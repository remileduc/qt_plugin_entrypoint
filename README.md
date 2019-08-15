<!--
    MIT License

    Copyright (c) 2019 Rémi Ducceschi

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE
-->

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](./LICENSE)

qt_plugin_entrypoint
====================

Demonstration of entry points in C++ thanks to Qt.

The goal is to be able to implement entry points, in the sense of Python ([pkg_resources entry points](https://setuptools.readthedocs.io/en/latest/pkg_resources.html#entry-points)), in a C++ Qt plugin architecture.

See section [Why](#why) below for more information.

[How to use](#how-to-use)

- [Prerequisites](#prerequisites)
- [Compile](#compile)
- [Run](#run)

[Why](#why)

[Code explanation](#code-explanation)

- [Architecture](#architecture)
- [Features](#features)
- [How it works](#how-it-works)

[Improvements](#improvements)

How to use
----------

In order to run this project, you need to install some stuff and compile.

It should work on both Linux and windows.

### Prerequisites ###

You need the following:

- Qt 5.9+
- a C++17 compiler (tested on MSVC 2019 and G++ 8.3)
- CMake 3.10+ (only tested with 3.14)

### Compile ###

You have to make the project with CMake:

```bash
mkdir build
cd build
cmake -G "Unix Makefiles" -A x64../source
```

You can use the CMake generator of your choice: <https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#cmake-generators>

If you prefer, you can open the [source/CMakeLists.txt](./source/CMakeLists.txt) fils in QtCreator, it will automatically generate the project for you.

Then, you can build with your IDE or directly with

```bash
make
```

### Run ###

Once compiled, you can launch the created executable `MainApp` or `MainApp.exe`. If everything went fine, it will automatically load the 3 plugins that have been build next to the executable (`.dll` or `.so` files).

Note that the executable should be located in the subfolder `build/main_app`.

Why
----

For the development of [SurveyPad](https://gitlab.cern.ch/apc/susofts/interfaces/SurveyPad/), we need an architecture based on plugins. Plugins can be written by anybody, so their code is in seperated repositories. Thus, plugins can't have any dependencies between each others. And you can't assume that a plugin will necessarily always be here at run time...

However, we have reached a point where we would like some plugin to expose, or to use, an entry point, as defined by [pkg_resources](https://setuptools.readthedocs.io/en/latest/pkg_resources.html#entry-points) in Python:

```
                   +-------------+
                   | Application |
                   +------+------+
                          |
                   +------+------+
                   |    Utils    |
                   +------+------+
       +--------------^   ^   ^--------------+
       |                  |                  |
+------+------+    +------+------+    +------+------+
|  Plugin 1   |    |  Plugin 2   |    |  Plugin 3   |
+-------------+    +-------------+    +-------+-----+
         | |           |                 |
         | +-----------+                 |
         +-------------------------------+
```

Globally, we would like to implement the 2 lines at the bottom, between `Plugin 1` and `Plugin 2`, and between `Plugin 1` and `Plugin 3`, without adding any dependencies between the plugins.

One solution could be to add some interfaces in `Utils`, but we don't want plugin specific code there...

So we took the other solution: the one with entry points. Globally, one plugin says in its metadata that he has an entry point (represented by a class name) that others can use, if they want. Then, another plugin that wants to use this entry point can look for it amoung all the plugins that are available at run time. If it finds the correct entry point, it can use it.

In reallity, he needs to instantiate the class exposed by the the first one in its metadata. And here we face the main problems:

1. instantiate an object from its class name as a string?
	- in Python, you can
	- in C++, NO! (the closest you can have are templates, but you need to know the class at compile time...)
2. run a method from a class you don't know
	- in Python, you use duck typing (don't have to inherit an interface to implement it)
	- in C++, NO! (you must inherit a class to implement its interface)

The first point can be fixed thanks to Qt and its [QMetaType](https://doc.qt.io/qt-5/qmetatype.html). Dummy example:

```cpp
#include <QMetaType>
#include <QDebug>
#include <QVariant>

class MyClass
{
public:
    virtual ~MyClass()  = default;
    int getValue() const noexcept { return value; }
    void setValue(int i) noexcept { value = i; }
private:
    int value;
};
Q_DECLARE_METATYPE(MyClass);

int main(int argc, char *argv[])
{
    {
        // WARNING!!! YOU **NEED** THIS LINE
        // Otherwise, the class won't be registered in the Qt system...
        QVariant v = QVariant::fromValue(MyClass());
    }

    int id = QMetaType::type("MyClass");
    if (id == QMetaType::UnknownType)
        return 1;
    // Now you can instantiate an object of MyClass by its name!
    // note the static_cast that can be dangerous...
    // This is because QMetaType::create() returns a void*
    MyClass *myClassPtr = static_cast<MyClass*>(QMetaType::create(id));
    myClassPtr->setValue(8);
    qDebug() << "LOOOL" << myClassPtr->getValue();
    QMetaType::destroy(id, myClassPtr);

    return 0;
}
```

The second point is a bit trickier... Current solution is to define an interface in the plugin that creates the entry point. Then, all the plugins that want to use it will copy the `.hpp` file in their repository to be able to implement the interface. Not the most beautiful, but so far it works (though we are stuck with pure abstract class).

Code explanation
----------------

### Architecture ###

The project is composed of 4 projects:

- utils: a static library used in all other projects
- main_app: the main application
- plugin_cat: a first plugin representing a cat
- plugin_dog: a second plugin representing a dog
- plugin_frog: a third plugin representing a frog

It is the same as the graphic above, with `plugin_cat` for `Plugin 1`, `plugin_dog` for `Plugin 2` and `plugin_frog` for `Plugin 3`.

Globally, we have one executable and 3 dynamic libraries (`.dll` or `.so`) created thanks to the [Qt Plugin system](https://doc.qt.io/qt-5/plugins-howto.html#the-low-level-api-extending-qt-applications).

The `utils` project defines the interface for a plugin, this is the common point for all the others projects. Indeed, `main_app` needs to know this interface on order to be able to load the plugins that implements it.

### Features ###

When you launch the application, the followin happens:

- the main widget is created in `main.cpp`
- the constructor of the main widget `MainApp` will automatically load all the available plugins
- now you can see what the plugins have to say by selecting a plugin from the combobox.

Now, what we want is to have some communication between the plugins:
- `plugin_cat` is an ennemy of `plugin_dog`
- `plugin_frog` is a friend of `plugin_dog`
- `plugin_frog` tries to help `plugin_cat` and tells him when the dog is in the area

### How it works ###

`plugin_dog` can have ennemies and friends. Both need to implement the same interface: [DogInterface](./source/plugin_dog/DogInterface.hpp). However, if you want to be friend, you need to use the entrypoint `PluginDog_friend`, and use `PluginDog_ennemies` to be an ennemy.

Let's take a frog for instance. It want to be a friend of dogs, thus, it first copies the [DogInterface (from plugin_frog)](./source/plugin_frog/DogInterface.hpp), and implements it in [DogFriend](./source/plugin_frog/DogFriend.hpp). Here, the class is exposed to Qt thanks to the line `Q_DECLARE_METATYPE(DogFriend)`. Note that it also needs to add this dummy line in [PluginFrog.cpp](./source/plugin_frog/PluginFrog.cpp#L9-L10): `QVariant::fromValue(DogFriend());`.

Now, in its [JSON metadata](./source/plugin_frog/PluginFrog.json), it can use the entry point `PluginDog_friend` to expose the class:

```json
{
	"PluginDog_friend": "DogFriend"
}
```

Thus, when `plugin_dog` checks for its friends, it can see that he can instantiate a class named `"DogFriend"` and use it: [PluginDog.cpp#L34-L49](./source/plugin_dog/PluginDog.cpp#L34-L49)

Same mechanism happens for the cat.

Improvements
------------

Any code improvements, suggestions... are welcome!!!
