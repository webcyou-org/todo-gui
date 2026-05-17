#ifndef RUST_FUI_QCLIPBOARD_H
#define RUST_FUI_QCLIPBOARD_H

#ifdef __cplusplus
extern "C" {
#endif

void QClipboard_setText(void *self, void *text, int mode);
void* QClipboard_text(void *self, int mode);

#ifdef __cplusplus
}
#endif

#endif //RUST_FUI_QCLIPBOARD_HH
