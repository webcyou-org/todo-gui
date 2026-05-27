# Zig / Qt Todo

Zig + Qt6 Widgets で実装した Todo アプリ。  
Zig がデータモデルを管理し、Qt6 C++ が UI を担当する。C ブリッジ経由で双方向通信を行う。

## Requirements

- macOS (arm64)
- [Zig](https://ziglang.org/) 0.16.0
- Qt 6 (`brew install qt`)

## Build

```sh
zig build
```

## Run

```sh
zig build run
# または
./zig-out/bin/todo
```

## File Structure

```
src/
├── main.zig       # エントリーポイント + C コールバック + pushUI()
├── data.zig       # AppState / Todo / TabFilter データモデル
├── qt_bridge.h    # Zig↔Qt の C インターフェース宣言
├── qt_app.cpp     # Qt6 Widgets による全 UI 実装
└── theme.h        # デザイントークン定数（色・サイズ）
```

## Architecture

MVC パターンを採用。Zig がデータモデルを保持し、Qt6 C++ が View を担当する。  
C 関数ブリッジ（`qt_bridge.h`）を介してコールバックを双方向に呼び出す。

| レイヤー | ファイル | 役割 |
|---------|---------|------|
| Model | `data.zig` | AppState・Todo リスト・TabFilter の状態管理 |
| View | `qt_app.cpp` | Qt Widgets による UI 描画・イベント受付 |
| Controller | `main.zig` | `export fn` コールバックで Qt→Zig 橋渡し、`pushUI()` で Zig→Qt 更新 |

## Notes

- `callconv(.c)` **小文字** — Zig 0.14 以降の C 呼び出し規約（`.C` 大文字は廃止）
- `export fn` + `extern fn` で双方向 C ブリッジを構築、Q_OBJECT / MOC 不要
- 全シグナルをラムダ接続 `connect(widget, &Signal, lambda)` → カスタム Q_OBJECT クラス不要
- `QStyleFactory::create("Fusion")` — macOS ネイティブスタイルを Fusion に切り替えることで QStyleSheet が完全に適用される
- `deleteLater()` — シグナルハンドラ内からウィジェットを安全に削除するための Qt 慣用句
- プレースホルダーテキスト色は `QPalette::PlaceholderText` で設定（stylesheet の `color` では効かない場合あり）
- `on_ready` コールバック — Qt 側の UI セットアップ完了後に呼ばれ、初期データを `qt_update_todos` で流し込む