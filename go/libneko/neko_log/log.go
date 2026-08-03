package neko_log

// LogLevel represents the severity of a log message
type LogLevel int

const (
Debug LogLevel = iota
Info
Warn
Error
)

// Logger interface
type Logger interface {
Log(level LogLevel, msg string)
}

// Default logger implementation
type DefaultLogger struct{}

func (l *DefaultLogger) Log(level LogLevel, msg string) {
// Simple logging implementation
}

var defaultLogger = &DefaultLogger{}

func GetLogger() Logger {
return defaultLogger
}
