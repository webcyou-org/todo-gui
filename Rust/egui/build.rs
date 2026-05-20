fn main() {
    #[cfg(target_os = "macos")]
    {
        cc::Build::new()
            .file("src/ime_mac.m")
            .flag("-fobjc-arc")
            .compile("ime_mac");
        println!("cargo:rustc-link-lib=framework=Cocoa");
    }
}