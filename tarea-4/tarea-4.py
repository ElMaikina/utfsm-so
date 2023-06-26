import threading
import random
import time
import datetime


class Juego:
	def __init__(self, nombre, cap_fila, dur, cap_juego):
		# Condiciones iniciales
		self.capacidad_de_juego = cap_juego
		self.capacidad_de_fila = cap_fila
		self.nombre = nombre
		self.duracion = dur

		# Cantidad de personas actuales
		self.personas_en_juego = 0
		self.personas_en_fila = 0

		# Candados para el estado del juego
		self.puede_entrar_a_fila = threading.Semaphore(value=cap_fila)
		self.puede_entrar_a_juego = threading.Lock()

# Crea los juegos con los parametros indicados por la tarea
juegos = []
juegos.append(Juego("Montaña_Rusa", 10, 9, 10))
juegos.append(Juego("Casa_Terror", 8, 5, 2))
juegos.append(Juego("Carrusel", 15, 7, 5))
juegos.append(Juego("Barco_Pirata", 6, 4, 3))

# Total de personas que entraron al parque hoy
total_de_personas = 150
personas_en_zona_comun = total_de_personas

# La persona busca entretencion, asi que magicamente 
# piensa en dos juegos a los cual subirse
def ser_persona():
    uno = random.randint(0, 3)  # Primer juego
    dos = random.randint(0, 3)  # Segundo juego

    print("Soy una Persona, y quiero ir a ", end="")
    print(juegos[uno].nombre, end="")
    print(" y luego a ", end="")
    print(juegos[dos].nombre)

    juegos[uno].puede_entrar_a_fila.acquire()  # Revisa si puede entrar a la fila del primer juego

    # Obtener la hora actual
    hora_actual = datetime.datetime.now().strftime("%H:%M:%S.%f")

    print("    * Alguien entro a la fila de", juegos[uno].nombre, "*")

    global personas_en_zona_comun
    personas_en_zona_comun -= 1  # Sale de la Zona Comun
    print("    * Zona Comun:", str(personas_en_zona_comun), "*")

    juegos[uno].personas_en_fila += 1  # Entra a la fila
    hora_entrada_fila_uno = datetime.datetime.now().strftime("%H:%M:%S.%f")
    print("    * Fila de", juegos[uno].nombre, ":", juegos[uno].personas_en_fila, "*")

    if juegos[uno].personas_en_fila == juegos[uno].capacidad_de_fila:  # Si la fila llega al numero deseado, empieza el juego
        juegos[uno].puede_entrar_a_fila.release()  # Todos salen de la Fila
        juegos[uno].personas_en_fila = 0
        juegos[uno].puede_entrar_a_juego.acquire()  # Todos entran al juego
        print("    * Empezo", juegos[uno].nombre, "*")
        hora_entrada_juego_uno = datetime.datetime.now().strftime("%H:%M:%S.%f")
        time.sleep(juegos[uno].duracion)  # Se espera hasta que termine el juego
        print("    * Termino", juegos[uno].nombre, "*")
        juegos[uno].puede_entrar_a_juego.release()  # Se vacia el juego
        # Registrar entrada juego uno
        with open(juegos[uno].nombre+".txt", "a") as archivo:
            archivo.write(f"Persona, {hora_entrada_fila_uno}, {hora_entrada_juego_uno}, 1\n")

    juegos[uno].puede_entrar_a_fila.release()
    personas_en_zona_comun += 1  # Vuelve de la Zona Comun

    juegos[dos].puede_entrar_a_fila.acquire()
    print("    * Alguien entro a la fila de", juegos[dos].nombre, "*")
    personas_en_zona_comun -= 1
    print("    * Zona Comun:", str(personas_en_zona_comun), "*")

    juegos[dos].personas_en_fila += 1
    hora_entrada_fila_dos = datetime.datetime.now().strftime("%H:%M:%S.%f")
    print("    * Fila de", juegos[dos].nombre, ":", juegos[dos].personas_en_fila, "*")

    if juegos[dos].personas_en_fila == juegos[dos].capacidad_de_fila:
        juegos[dos].puede_entrar_a_fila.release()
        juegos[dos].personas_en_fila = 0
        juegos[dos].puede_entrar_a_juego.acquire()
        print("    * Empezo", juegos[dos].nombre, "*")
        hora_entrada_juego_dos = datetime.datetime.now().strftime("%H:%M:%S.%f")
        time.sleep(juegos[dos].duracion / 100)
        print("    * Termino", juegos[dos].nombre, "*")
        juegos[dos].puede_entrar_a_juego.release()
        # Registrar entrada juego dos
        with open(juegos[dos].nombre+".txt", "a") as archivo:
            archivo.write(f"Persona, {hora_entrada_fila_dos}, {hora_entrada_juego_dos}, 2\n")

    juegos[dos].puede_entrar_a_fila.release()
    hora_salida = datetime.datetime.now().strftime("%H:%M:%S.%f")

    # Registrar las entradas a las filas de las atracciones en el archivo
    with open("Zona_Comun.txt", "a") as archivo:
        archivo.write(f"Persona, {hora_actual}, ")
        archivo.write(f"{juegos[uno].nombre}, {hora_entrada_fila_uno}, ")
        archivo.write(f"{juegos[dos].nombre}, {hora_entrada_fila_dos}\n")

    with open("Salida.txt", "a") as archivo:
        archivo.write(f"Persona, {hora_salida}\n")
              


# Funcion main
open("Zona_Comun.txt", "w")
open("Montaña_Rusa.txt", "w")
open("Casa_Terror.txt", "w")
open("Carrusel.txt", "w")
open("Barco_Pirata.txt", "w")
open("Salida.txt", "w")
if __name__ == '__main__':
	for persona in range(total_de_personas):
		persona = threading.Thread(target=ser_persona(), args=())
		persona.daemon = True
		persona.start