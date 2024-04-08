# Adding a new graphical library to the arcade

To add a new graphical library to the arcade, follow these steps:

## 1. Graphical library interface

All graphical libraries in the arcade are based on the same interfaces. These interfaces are prefixed with the letter 'I', such as **IGraphicalModule**, **IGraphics** or **IWindow**. You can find these interfaces in the [Arcade GitHub repository](https://github.com/milimarg/Arcade-Groupes).

## 2. Implement the graphical library

Create a new graphical library that implements the necessary interfaces. This library should provide functionality for rendering graphics, managing windows, and retrieving user input. Ensure that the graphical library is compatible with the arcade's runtime environment.

Make sure to implement an extern C following this exact format:

```cpp
extern "C" {
    std::string getType() {
        return "graphical";
    }

    std::unique_ptr<arcade::IGraphicalModule> entryPoint() {
        return std::make_unique<arcade::GraphicalLibraryName>();
    }
}
```

## 3. Compile the graphical library

Compile the graphical library into a shared object (`.so`) file. Make sure to include any necessary dependencies and libraries required for rendering graphics and handling input.

## 4. Update the library folder

Place the compiled shared object in the `./lib` folder of the arcade. This allows the arcade to detect and load the new graphical library at runtime.

## 5. Test the integration

Test the integration of the new graphical library with the arcade. Launch the arcade and verify that the new graphical features are available and functioning correctly. Ensure that the graphical library provides a smooth and responsive user experience.

## 6. Documentation and resources

Provide documentation for the new graphical library, including instructions on how to use its features and any additional information that developers may need. Consider creating a README file within the graphical library's repository to document its functionality and usage.
