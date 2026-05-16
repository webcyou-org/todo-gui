// Single shared @cImport so all modules agree on NkApp's opaque type.
pub const c = @cImport({ @cInclude("nk_app.h"); });