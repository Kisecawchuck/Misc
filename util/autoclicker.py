from pynput.mouse import Button, Controller
import time

mouse = Controller()
interval = float(input("Intervalo: "))  # segundos

# Posição inicial do mouse
last_position = mouse.position

try:
    while True:
        # Verifica se o mouse foi movido
        if mouse.position != last_position:
            print("Mouse movimentado. Auto-clicker parado.")
            break
        mouse.click(Button.left)
        time.sleep(interval)

except KeyboardInterrupt:
    print("Auto-clicker interrompido pelo teclado.")
