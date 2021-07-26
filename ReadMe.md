# Coding assigment Electrolux

This project is to an command line application that converts between two currencies using  http://fixer.io/ and written in C++ running in MacOS.

##Running requirement(MacOS)

This project uses CMake to manage dependecies, if you don't have it installed run: 
~~~
brew install cmake
~~~


To build the project, run the shell script via terminal:
~~~
bash start.sh
~~~

Optional : if you are using CLion to run the application, run the following command to rectrive the submodule:
~~~
git submodule init
git submodule update
~~~

To run the command line application:
~~~
cd build
./run [Argument1 base currrency] [Argument2 target currrency] [Argument3 amount]
[comment]: <> (for example, if you want to convert 100 US dollars to Euro, in the terminal type ./run USD EUR 100)
~~~

To run the unit test from the build reposity:
~~~
cd test
./CurrencyAppTests
~~~

This application takes three command-line arguments which are base currency, target currency and amount. The application uses the CURL library(with MacOS built-in) to initialize the CURL object with the given URL from fixer.io API to retrieve the real-time currency ratio and return a JSON object. Once the application receives the JSON object,  the application clean up the CURL buffer and free up the memory, then it uses [nlohmann/json](https://github.com/nlohmann/json) library to parse the JSON, get the time stamp and create an unordered_map with each currency and its rate pair. Then matching with the user input from the command line, to return the result. If the user input is not matched with the unordered_map key-value pair, the application will catch the out-of-range error and print all the available currency. The unit test uses the [GoogleTest](https://google.github.io/googletest/quickstart-cmake.html) library.   

