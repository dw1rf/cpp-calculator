
#include "calculator.h"

int main() {
    const bool finishedNormally = RunCalculatorCycle();

    if (!finishedNormally) {
        return 1;
    }

    return 0;
}
