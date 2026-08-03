package neko_common

// Version information
var (
Version_neko = "dev"
Version_v2ray = "unknown"
)

// AppType represents the type of application
type AppType int

const (
AppType_NekoRay AppType = 1
AppType_NekoBox AppType = 2
)
