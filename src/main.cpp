#include <mbed.h>
#include <string>
#include "util/frdm_fc_io.h"
#include "bluetooth/tinysine.h"
#include "util/logcat.h"

using namespace mbed;
using namespace frdm_fc;

static const char          *kTag      = "main";
static logcat::ISink       *cons_sink = nullptr;
static bluetooth::TinySine *tiny_sine = nullptr;

static void LogInit() {
    auto logcat = logcat::Shared();
    cons_sink = new logcat::ConsoleSink;
    logcat->AddSink(cons_sink);
    logcat->SetLevelGlobal(logcat::level::DEBUG);
    logcat->I(kTag, "FRDM-Kxxx Fan Controller Firmware v0.1");
}


static void BluetoothInit() {
    auto lc      = logcat::Shared();
    auto bt_uart = io::GetBluetoothUART();
    lc->I(kTag, "Initializing bluetooth module...");
    tiny_sine = new bluetooth::TinySine(bt_uart);
    if (!tiny_sine->DetectBaudrate()) {
        lc->E(kTag, "Tinysine not responding");
        exit(-1);
    }
    auto vers = tiny_sine->GetVersion();
    lc->I(kTag, "Tinysine firmware version = %s", vers.c_str());
    lc->I(kTag, "Bluetooth ready.");
}

static void BluetoothUART_ISR() {
    auto bt   = io::GetBluetoothUART();
    auto cons = io::GetConsoleUART();
    while (bt->readable()) {
        cons->putc(bt->getc());
    }
}

int main() {
    LogInit();
    BluetoothInit();
    Thread::wait(osWaitForever);
    return 0;
}
