import org.jetbrains.compose.desktop.application.dsl.TargetFormat

plugins {
    kotlin("jvm") version "2.0.21"
    id("org.jetbrains.compose") version "1.6.11"
    id("org.jetbrains.kotlin.plugin.compose") version "2.0.21"
}

group = "com.example"
version = "1.0-SNAPSHOT"

dependencies {
    implementation(compose.desktop.currentOs)
    implementation(compose.material3)
}

compose.desktop {
    application {
        mainClass = "MainKt"
        nativeDistributions {
            targetFormats(TargetFormat.Dmg)
            packageName = "todo"
            packageVersion = "1.0.0"
        }
    }
}
