import gpiozero as zero
from time import sleep

if __name__ == "__main__":
    mcp3008 = zero.MCP3008(7);
    while True:
        print("the channel 7 vlaue is {:.2f}".format(mcp3008.value));
        sleep(1)