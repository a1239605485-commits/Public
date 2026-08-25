# 生命锁定测试 Mod

基于官方 KernelLoader ABI：后置 Hook `Terraria.Player.Update(int)`，每帧把
`statLife` 恢复为 `statLifeMax2`。为避免破坏死亡流程，仅在当前生命大于 0
时恢复；因此它用于验证普通非致命伤害是否会立即回满。

Android ARM64 构建使用 NDK r28：

```sh
cmake --preset ci-android-arm64-release
cmake --build --preset ci-android-arm64-release
```

GitHub Actions 会自动生成可安装 ZIP。
