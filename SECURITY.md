# Security Policy

## Supported Versions

| Version | Supported          |
| ------- | ------------------ |
| 3.26+   | :white_check_mark: |
| < 3.26  | :x:                |

## Reporting a Vulnerability

We take the security of NekoRay seriously. If you believe you have found a security vulnerability, please report it to us as described below.

**Please do NOT report security vulnerabilities through public GitHub issues.**

Instead, please report them via email at: security@nekoray.moe (placeholder)

You should receive a response within 48 hours acknowledging your report. After the initial reply to your report, we will send periodic updates about the progress toward a fix and full announcement.

## Security Best Practices

### For Users

1. **Keep Software Updated**: Always use the latest version of NekoRay to benefit from security patches.

2. **Verify Downloads**: 
   - Download only from official sources (GitHub Releases)
   - Verify checksums when available
   - Check GPG signatures for releases

3. **Configuration Security**:
   - Never share your configuration files publicly
   - Use strong encryption for sensitive data
   - Regularly rotate credentials and keys

4. **Network Security**:
   - Only connect to trusted servers
   - Verify server certificates
   - Use TLS/SSL whenever possible

5. **System Permissions**:
   - Run with minimal required permissions
   - Avoid running as root/admin unless necessary
   - Review permission requests carefully

### For Developers

1. **Code Security**:
   - Follow secure coding practices
   - Use static analysis tools (clang-tidy, CodeQL)
   - Review code for security issues before merging

2. **Dependency Management**:
   - Keep dependencies up to date
   - Monitor for security advisories
   - Use dependency scanning tools

3. **Input Validation**:
   - Validate all user inputs
   - Sanitize data before processing
   - Implement proper error handling

4. **Memory Safety**:
   - Prefer smart pointers over raw pointers
   - Use RAII for resource management
   - Avoid buffer overflows and use-after-free

5. **Cryptography**:
   - Use established cryptographic libraries
   - Never implement custom crypto algorithms
   - Keep cryptographic parameters up to date

## Security Features

### Current Implementation

- **Encrypted Storage**: Sensitive configuration data is encrypted
- **Secure Communication**: gRPC with TLS support
- **Input Validation**: Comprehensive input validation on all user inputs
- **Memory Safety**: Modern C++ practices with smart pointers

### Planned Improvements

- [ ] Hardware security module (HSM) support
- [ ] Enhanced certificate pinning
- [ ] Automated security scanning in CI/CD
- [ ] Bug bounty program
- [ ] Third-party security audit

## Known Limitations

1. **Legacy Code**: Some components may use older patterns that are being gradually modernized
2. **Third-party Dependencies**: Security depends on upstream dependencies
3. **Platform Differences**: Security features may vary by platform

## Security Updates

Security updates are released as soon as possible after a vulnerability is confirmed and fixed. Updates are distributed through:

- GitHub Releases
- Package managers (AUR, etc.)
- In-app update notifications (where available)

## Recognition

We appreciate responsible disclosure and will acknowledge researchers who report valid security issues (unless they prefer to remain anonymous).

## Contact

For security-related questions or concerns:
- Email: security@nekoray.moe (placeholder)
- GitHub: Use private vulnerability reporting feature

---

Last updated: 2024
