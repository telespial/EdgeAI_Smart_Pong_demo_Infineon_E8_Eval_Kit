# START_HERE

## Goal
Port Smart Pong onto the PSOC Edge E84 Evaluation Kit (EPC2) using the known-good LVGL graphics pipeline.

## Current Baseline (2026-03-21)
- Board + display boot confirmed with flashed firmware
- Display: Waveshare 4.3-inch (800x480)
- Existing app: LVGL music demo with `CUSTOM BUILD` banner
- Smart Pong prep entry screen is scaffolded and build-gated

## Read Order
1. `../README.md`
2. `PROJECT_STATE.md`
3. `HARDWARE_SETUP.md`
4. `OPS_RUNBOOK.md`
5. `SMART_PONG_PORT_PLAN.md`
6. `TODO.md`

## Source Of Truth
- Runtime entry: `../proj_cm55/main.c`
- Smart Pong scaffold: `../proj_cm55/app/EdgeAI_Smart_Pong_demo_Infineon_E8_Eval_Kit/`
- Display selection: `../common.mk` (`CONFIG_DISPLAY`)

## Mode Switch
- Default: music demo (`APP_SMART_PONG_MODE=0`)
- Smart Pong prep screen: set `APP_SMART_PONG_MODE=1` in `proj_cm55/Makefile`
