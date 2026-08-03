# Code Style Guide for NekoRay

This document describes the coding standards and style guidelines for the NekoRay project, updated for modern C++23 and Qt 6 conventions.

## C++ Standard

- **C++23** is the minimum required standard
- Compiler must support C++23 features
- Use `set(CMAKE_CXX_STANDARD 23)` in CMakeLists.txt

## Naming Conventions

### Files
- Header files: `.hpp` for C++ headers, `.h` for C headers or Qt moc files
- Source files: `.cpp`
- Use PascalCase for class names in filenames (e.g., `MainWindow.cpp`)
- Use lowercase with underscores for utility files (e.g., `neko_utils.cpp`)

### Classes and Types
- Use PascalCase: `MainWindow`, `ProfileFilter`, `ConfigBuilder`
- Abstract classes should be prefixed with `Abstract`: `AbstractBean`
- Qt widgets should be prefixed with their type: `DialogEditProfile`, `WidgetProxyItem`

### Functions and Methods
- Use PascalCase: `LoadData()`, `SaveConfiguration()`
- Private methods can use camelCase: `loadDataInternal()`
- Getters: `GetSomething()`, `something()` (Qt style)
- Setters: `SetSomething()`, `setSomething()` (Qt style)

### Variables
- Use camelCase: `profileName`, `connectionTimeout`
- Member variables: `m_profileName` or `profile_name_`
- Global variables: `g_connectionManager`
- Constants: `kMaxConnections`, `MAX_BUFFER_SIZE`
- Static variables: `s_instanceCount`

### Namespaces
- Use lowercase with underscores: `NekoGui`, `NekoCore`
- Avoid `using namespace` in header files

## Modern C++ Features

### Smart Pointers
Prefer smart pointers over raw pointers:
```cpp
std::unique_ptr<Profile> profile = std::make_unique<Profile>();
std::shared_ptr<Connection> conn = std::make_shared<Connection>();
```

### Auto Keyword
Use `auto` when type is obvious:
```cpp
auto iter = container.begin();
auto result = computeValue();
```

Avoid `auto` when type clarity is important:
```cpp
int errorCode = getErrorCode();  // Clear type is better
```

### Range-based For Loops
```cpp
for (const auto& item : collection) {
    process(item);
}
```

### Lambda Expressions
```cpp
std::sort(items.begin(), items.end(), [](const auto& a, const auto& b) {
    return a.priority() > b.priority();
});
```

### constexpr and consteval
Use `constexpr` for compile-time computations:
```cpp
constexpr int getMaxConnections() { return 100; }
```

### std::optional
Use `std::optional` instead of pointer returns for nullable values:
```cpp
std::optional<Profile> findProfile(const QString& id);
```

### std::variant and std::any
Use for type-safe unions instead of void pointers or inheritance hierarchies.

## Qt-Specific Guidelines

### Qt 6 Modernizations
- Use `qt_add_executable()` instead of manual target creation
- Use `qt_add_lupdate()` and `qt_add_lrelease()` for translations
- Prefer `QSignalMapper` replacements with lambda connections
- Use `Q_ENUM` instead of `Q_ENUMS`

### Signal/Slot Connections
Use function pointers for type-safe connections:
```cpp
connect(button, &QPushButton::clicked, this, &MainWindow::handleClick);
```

Use lambdas for complex operations:
```cpp
connect(service, &Service::dataReady, this, [this](const QByteArray& data) {
    processData(data);
    updateUI();
});
```

### QObject Memory Management
- Use parent-child relationships for automatic cleanup
- Use `QPointer` for safe cross-object references
- Prefer `QObject::deleteLater()` over direct deletion in slots

### QString and Containers
- Use `QStringView` for read-only string operations
- Use `qAsConst()` for read-only iterations
- Prefer STL algorithms with Qt containers

## Error Handling

### Exceptions
- Use exceptions for exceptional conditions only
- Document exception specifications
- Catch by reference: `catch (const std::exception& e)`

### Qt Error Handling
- Check `QFile::error()` after file operations
- Use `Q_ASSERT()` for development-time checks
- Return `std::optional` or `QResult` for expected failures

## Documentation

### Comments
- Use Doxygen-style comments for public APIs:
```cpp
/// @brief Brief description
/// @param name Parameter description
/// @return Return value description
QString formatName(const QString& name);
```

- Use `//` for inline comments
- Keep comments up-to-date with code changes

### README and Documentation
- Keep README.md up-to-date
- Document build requirements and dependencies
- Include usage examples

## Testing

### Unit Tests
- Write tests for critical functionality
- Use Google Test or Qt Test framework
- Aim for >80% code coverage on core modules

### Integration Tests
- Test component interactions
- Include end-to-end scenarios

## Build System

### CMake
- Use modern CMake (3.28+)
- Use target-based commands
- Avoid global variables
- Use `target_link_libraries()` with visibility specifiers

### Dependencies
- Document all dependencies
- Use package managers when possible
- Pin dependency versions for reproducibility

## Security Considerations

### Input Validation
- Validate all user inputs
- Sanitize data before processing
- Use secure string handling

### Memory Safety
- Prefer smart pointers
- Avoid raw `new`/`delete`
- Use RAII for resource management

### Network Security
- Validate certificates
- Use TLS for network communications
- Implement proper timeout handling

## Performance

### Optimization Guidelines
- Profile before optimizing
- Use move semantics where appropriate
- Avoid unnecessary copies
- Use `const` references for large objects

### Threading
- Use `QThread` or `std::thread` appropriately
- Protect shared data with mutexes
- Avoid deadlocks with consistent lock ordering
- Use atomic operations for simple counters

## Version Control

### Git Commits
- Write clear commit messages
- Reference issues in commits
- Keep commits atomic and focused

### Branching
- Use feature branches
- Rebase before merging to main
- Delete merged branches

## Code Review Checklist

- [ ] Code follows style guidelines
- [ ] No compiler warnings
- [ ] Tests pass
- [ ] Documentation updated
- [ ] No security vulnerabilities introduced
- [ ] Performance impact considered
- [ ] Backwards compatibility maintained (if applicable)

## Tools

### Required Tools
- Clang 17+ or GCC 13+
- CMake 3.28+
- Qt 6.5+
- clang-format (for code formatting)
- clang-tidy (for static analysis)

### Recommended IDE Extensions
- CLion or Qt Creator
- VS Code with C++ extensions
- EditorConfig support

## Continuous Integration

- Run tests on every PR
- Check code formatting automatically
- Perform static analysis
- Build on all supported platforms

---

Last updated: 2024
Version: 1.0
