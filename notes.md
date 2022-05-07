# Zapoctak notes

In CMake you can specify the minimal required C++ version with [CXX_STANDARD_REQUIRED](https://cmake.org/cmake/help/v3.10/prop_tgt/CXX_STANDARD_REQUIRED.html#prop_tgt:CXX_STANDARD_REQUIRED).

I like the life hack :-D. I'm not aware of any bash autocompletion for C++ interfaces so this is cool little trick. Although my bet is that there are some.

### static vs. member functions in CLI parser

>Lots of member functions in `CommandLineParser` are static yet they take an instance of `CommandLineParser` as their parameter, which can look a bit odd. It is because the map between commands and member functions utilizes `std::function` which works better with static functions, yet I needed to access members of the `CommandLineParser` instance, so in the end I decided to use static member functions with `CommandLineParser` instance as a function parameter to meet these two requirements. 

So to address this, if something seems ugly, you are likely doing it wrong.
I see these options:

```c++
    using MapType = std::map<string, std::function<void()>>;

    MapType commandMap = {
        {"list", [this](){ this->ParseListParams(); }}
    };
```

This essentially binds the this parameter to a `std::function` object.
There is also `std::bind` and it was the "old way" of creating closures i.e. callable objects (functors) that have some data members like `this` pointer to the `CommandLineParser`.
Both `std::function` and `std::bind` are nicely explained in [Effective and Modern C++](https://www.oreilly.com/library/view/effective-modern-c/9781491908419/) by Scott Meyers, "Item2: Understand `auto` type deduction" resp. "Item34: Prefer lambdas to `std::bind`"

However, your issue is not about what methods to pass, it is in OOP design, more specifically compossition.
This can be seen directly from main:
```c++
int main(int argc, char * argv[]) {

    vector<string> args (argv + 1, argv + argc);
    CommandLineParser parser(args);
    parser.ParseArgs();
    return 0;
}
```

If I read this it says to me that this program just parses CLI arguments and does nothing else.
It doesn't indicate any presence of Model-View-Controller pattern - it is hidden in CommandLineParser as a property (class composition).
Classes should interact with each other via methods called on each other with loose coupling (different modules do not have many interactions) high cohesion (module does one thing and it does it good, it doesn't do anything extra - it leaves it for another module).

In this case specifically imagine a CLI parser for other language e.g. Python's `argparse` it does not hold any application logic, it just does what it is supposed to do - parse CLI arguments and provide them in some form.
That is a well defined module that has some interface on how it informs user about parsed arguments and then other modules interact with this.

### UI

Add note that this could be better expressed as an open API (on Model) that has a CLI interface (view) that has certain controllers (individual commands) that interact with the Model via its API.
That is gist of the MVC pattern where you may have another sort of interface e.g. a web application that communicates with your backend Model via specified API.


## Summary

What I'd like you to change:

* Restructure your object model, try to define modules with principles described above, beware of composition. Look into UML diagrams of MVC pattern and see what those [associations mean](https://www.visual-paradigm.com/guide/uml-unified-modeling-language/uml-aggregation-vs-composition/) in particullar reference, composition and aggregation.

* CMake is very minimalistic, if you want to restrict usage to some specific version specify it there

* Add tests for your Model's API. If you can write straight forward unit tests you can see that your program is somewhat well structured (no unnecessary compositions etc.)


*Tips:*

* In order to avoid time parsing and all this fuss you can try C++ date and time support in standard library - https://en.cppreference.com/w/cpp/chrono but it is C++20 only, already supported by MVSC and partially by others.
