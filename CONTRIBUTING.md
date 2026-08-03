# Contributing to NekoRay

Thank you for your interest in contributing to NekoRay! This document provides guidelines and instructions for contributing.

## Code of Conduct

Please read and follow our [Code of Conduct](CODE_OF_CONDUCT.md) to maintain a welcoming and inclusive community.

## Getting Started

### Prerequisites

- CMake 3.28 or higher
- Qt 6.5 or higher
- C++23 compatible compiler (GCC 13+, Clang 17+, or MSVC 2022+)
- Git

### Setting Up Development Environment

1. **Fork the repository**
2. **Clone your fork**:
   ```bash
   git clone https://github.com/YOUR_USERNAME/nekoray.git
   cd nekoray
   ```

3. **Initialize submodules**:
   ```bash
   git submodule update --init --recursive
   ```

4. **Create a branch**:
   ```bash
   git checkout -b feature/your-feature-name
   ```

### Building from Source

```bash
# Configure
cmake -B build \
  -DCMAKE_BUILD_TYPE=Debug \
  -DQT_VERSION_MAJOR=6 \
  -DCMAKE_CXX_STANDARD=23

# Build
cmake --build build --parallel $(nproc)

# Run
./build/nekoray
```

See platform-specific build guides in the `docs/` directory.

## Development Workflow

### Branch Naming

- `feature/description` - New features
- `fix/description` - Bug fixes
- `refactor/description` - Code refactoring
- `docs/description` - Documentation updates
- `test/description` - Test additions/modifications

### Commit Messages

Follow the [Conventional Commits](https://www.conventionalcommits.org/) specification:

```
feat: add support for new protocol
fix: resolve memory leak in connection handler
docs: update build instructions for Linux
style: format code according to style guide
refactor: simplify profile loading logic
test: add unit tests for ConfigBuilder
chore: update dependencies
```

### Code Style

- Follow the [Code Style Guide](CODE_STYLE.md)
- Run `clang-format` before committing:
  ```bash
  clang-format -i src/**/*.cpp src/**/*.hpp
  ```
- Ensure no compiler warnings

### Testing

Before submitting a PR:

1. Build successfully on your platform
2. Run existing tests:
   ```bash
   cd build
   ctest --output-on-failure
   ```
3. Test manually with various configurations
4. Check for memory leaks (valgrind, AddressSanitizer)

## Making Changes

### Good Practices

- Keep changes focused and atomic
- Write clear, descriptive commit messages
- Add comments for complex logic
- Update documentation as needed
- Include tests for new functionality

### What to Avoid

- Large, unfocused commits
- Breaking existing functionality without migration path
- Removing deprecation warnings without fixing the underlying issue
- Adding unnecessary dependencies
- Hardcoding values that should be configurable

## Pull Request Process

1. **Ensure your branch is up to date**:
   ```bash
   git fetch origin
   git rebase origin/main
   ```

2. **Squash commits** if necessary to maintain clean history

3. **Create a Pull Request** with:
   - Clear title following commit message format
   - Detailed description of changes
   - Reference to related issues
   - Screenshots for UI changes
   - Testing performed

4. **Address review feedback** promptly

5. **Pass CI checks** before merging

## Areas Needing Contribution

### High Priority

- [ ] Unit test coverage improvement
- [ ] Documentation translations
- [ ] Performance optimizations
- [ ] Security hardening
- [ ] Accessibility improvements

### Medium Priority

- [ ] Plugin system development
- [ ] Advanced routing features
- [ ] Enhanced statistics and monitoring
- [ ] Mobile companion apps

### Low Priority

- [ ] Theme customization
- [ ] Additional protocol support
- [ ] Integration with other tools

## Reporting Issues

### Bug Reports

Include:
- NekoRay version
- Operating system and version
- Steps to reproduce
- Expected behavior
- Actual behavior
- Screenshots/logs if applicable

### Feature Requests

Include:
- Problem you're trying to solve
- Proposed solution
- Alternative solutions considered
- Use cases

## Questions?

- Check existing [documentation](docs/)
- Search [existing issues](https://github.com/MatsuriDayo/nekoray/issues)
- Join community discussions (Telegram, Discord, etc.)

## Recognition

Contributors are recognized in:
- RELEASE_NOTES.md for significant contributions
- CONTRIBUTORS.md file
- GitHub contributors page

Thank you for contributing to NekoRay! 🎉
