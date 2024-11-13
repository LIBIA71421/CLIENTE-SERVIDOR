import socket
import time

WIFI_SSID = ""         
WIFI_PASSWORD = ""   
SERVER_PORT = 80               
TIMEOUT_DURATION = 10              

distance_value = 0
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('0.0.0.0', SERVER_PORT))  
server_socket.listen(1)

print(f'Server listening on port {SERVER_PORT}')

def get_led_response(distance):
    if distance < 10:
        print("Turning on 4 LEDs")
        return distance
    elif distance < 20:
        print("Turning on 3 LEDs")
        return distance
    elif distance < 30:
        print("Turning on 2 LEDs")
        return distance
    elif distance < 40:
        print("Turning on 1 LEDs")
        return distance
    else:
        print("Turning off all LEDs")
        return distance 

while True:
    client_socket, client_address = server_socket.accept()
    print(f'Client connected from {client_address}')

    last_activity_time = time.time() 
    
    try:
        while True:
            client_socket.settimeout(1.0) 
            try:
                data = client_socket.recv(1024).decode()
                if not data:
                    break

                print(f'Received: {data.strip()}')
                if data.startswith("distance="):
                    distance_value = int(data.split('=')[1])
                    print(f'Distance: {distance_value}')
                    client_socket.sendall("ACK\n".encode())
                elif data.startswith("GET"):
                    led_response = get_led_response(distance_value)
                    client_socket.sendall(f"{led_response}\n".encode())

                last_activity_time = time.time()
            except socket.timeout:
                if time.time() - last_activity_time > TIMEOUT_DURATION:
                    print("Client timed out. Closing connection.")
                    break

    finally:
        client_socket.close()
        print('Client disconnected')
