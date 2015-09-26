# Naming Conventions

Naming conventions in Voltz are heavily based off of
[C# naming conventions](https://msdn.microsoft.com/en-us/library/ms229043.aspx).

## Pascal Case
Pascal case capitalizes the first letter of the identifier and the first letter
of every word after.

`ThisIsPascalCase`

`thisIsNotPascalCase`
`NeitherisThis`
`orthis`

## Camel Case
Camel case does not capitalize the first letter of the identifier, but it
capitalizes the first letter of every following word.

`thisIsCamelCase`

`ThisisnotCamelcase`
`thisIsnotcamelCaseEither`

### Modules
Modules are Pascal Case. `Std::Sync`.

### Classes
Classes are Pascal Case. `Std::IO::FileOutputStream`.

### Protocols
Protocols are Pascal Case. `Std::IO::OutputStream`.

### Methods
Methods are Pascal Case. `WriteString:`.

### Properties
Properties are Pascal Case. `myArray.Count`.

### Enum Value
Enum Values are Pascal Case. `MyEnum::MyEnumValue`.

### Local Variables
Local Variables are typically Camel Case, although this is more of a matter of
preference. `myVariable`.

### Parameters
Parameters are Camel Case. `func(name)`.

# Defining Classes
