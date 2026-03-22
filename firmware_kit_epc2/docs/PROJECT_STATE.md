# PROJECT_STATE

## Project
PSOC Edge E84 Eval (EPC2), LVGL graphics base for Smart Pong port.

## Date
2026-03-22

## Working Hardware
- Kit: `KIT_PSE84_EVAL_EPC2`
- MCU detected during flash: `PSE846GPS2DBZC4A`
- Display: Waveshare 4.3-inch DSI panel on `J39`

## Build Configuration
- `TARGET=KIT_PSE84_EVAL_EPC2`
- `TOOLCHAIN=GCC_ARM`
- `CONFIG_DISPLAY=W4P3INCH_DISP`
- `APP_SMART_PONG_MODE=1` (golden active mode)

## Firmware State
- Build and program path verified with OpenOCD + KitProg3
- Latest visible behavior confirmed on device: boots directly into live game
- Smart Pong app path: `proj_cm55/app/EdgeAI_Smart_Pong_demo_Infineon_E8_Eval_Kit/`
- Full project rebuild/program verified after gameplay tuning and startup changes
- Current tuning validated on hardware:
  - `EDGEAI_FIXED_FPS=180`
  - Max ball speed cap increased by `+50%` over prior baseline
  - Startup splash removed to avoid text corruption transition

## Recent Changes
1. Raised fixed-step loop target from `60` to `180` FPS.
2. Increased global ball speed cap by `+50%`.
3. Removed boot title draw path so startup enters gameplay directly.
4. Rebuilt and programmed successfully on E8 EPC2 + 4.3-inch display profile.
5. Updated restore-point documentation for new golden/failsafe baseline.

## Next Milestones
1. Add classic Pong audio cues (wall vs paddle event tones) through E8 audio path.
2. Finalize audio level/latency tuning against speaker output.
3. Continue gameplay polish and render artifact hardening under high speed.
