#include <mbed.h>
#include <MLX90363.h>

SPI spi(D11, D12, D13);
Serial serial(USBTX, USBRX);  // tx, rx
MLX90363 mlx90363_1(D10, &spi);
MLX90363 mlx90363_2(D9, &spi);

int main() {
    spi.format(8,1);
    spi.frequency(500000);
    serial.baud(9600);
    wait(1);

    while(1) {
        if (mlx90363_1.Poll()) serial.printf("crc error 1\n");
        wait_ms(1);
        if (mlx90363_2.Poll()) serial.printf("crc error 2\n");
        serial.printf("Angel_1: %" PRId16 " Angel_2: %" PRId16 "\n",mlx90363_1.Get_Angel(),mlx90363_2.Get_Angel());
        wait_ms(1);
    }
}