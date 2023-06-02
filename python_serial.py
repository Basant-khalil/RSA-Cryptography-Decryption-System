import serial  #from pyserial package 
import struct  #import to decode the byte strings returned form the serial read
from serial.tools import list_ports
import inquirer

print('\033[2;30;43m HELLO! Launching Encryption / Decryption Program \033[0;0m')

# User types  "1"
  # board geratese public & private key
  # board saves private key
  # board returns to python public key 

# User types "2"
  # board receives message and public key
  # encrypts using recived public key
  # retuns encrypted message

# User types "3"
  # board rerceives eencrypted message
  # decypts using saved private key
  # returrns message

# -------------------------------- Setup Communication --------------------------------
# get all the ports on computer and find the one connected to the USB
ports = list(list_ports.comports())
port = ports[0]
for p in ports :
  if "usb" in p.device:
    port = p
  print(" Found device " + str(p.device))

# print the selected port connected to the board
print(" ** Selected Device: ", port.device)

with serial.Serial(port.device,115200) as ser:
  # receive message from board to coomfirmm it is set up and communicating 
  rec_message = ser.readline()
  print(str(rec_message)) 

  # -------------------------------- let user select task --------------------------------
  # give user menue items to select what they want the board to do
  while True:
    print('\033[5;30;43m Select task \033[0;0m')
    questions = [ inquirer.List('Task',
                    message="What task do you need to do?",
                    choices=[
                        '1 - Generate Public/Private Keys', 
                        '2 - Encrypt message (with someone else public key)', 
                        '3 - Decrypt message (that has been encoded with your public key)'],),]

    answers = inquirer.prompt(questions)
    print(answers["Task"])
    print("\n")       # print the task the user selected

    # given the selected task, communicate with board on next steps
    task_num = ord(answers["Task"][0]) - 48

    # -------------------------------- Task 1 --------------------------------
    if task_num == 1:
      print("Generating Public/Private Keys!")
      
      # tell board to generate key
      num = 1000
      st = f"{num:04d}"
      ser.write(st.encode('utf-8'))

      # recive public key value and output it
      key = int.from_bytes(ser.read(1), "little")
      
      print(f'\033[2;30;43m Your Public key is: \033[0;0m {key}')
    
    # -------------------------------- task 2 --------------------------------
    if task_num == 2:
      message = input("Please type in your message: ")
      key = input("Please type in the public key: ")

      # tell board to encrypt message with 
      num = 2000
      st = f"{num:04d}"
      ser.write(st.encode('utf-8'))

      # send board the message len & key
      key = int(key)
      ser.write(key.to_bytes(1, 'little'))
      received = ser.read(1)
      ser.write(len(message).to_bytes(1, 'little'))
      received = ser.read(1)

      # send board message

      for c in message:
        ca = ord(c)
        ser.write(ca.to_bytes(1, 'little'))
        received = ser.read(1)
    
      # recive encrypted message and output it
      encryptedMessage = ser.readline()
      encryptedMessage = list(encryptedMessage)
      print(type(encryptedMessage))
      
      print('\033[2;30;43m Your Decrypted Message is: \033[0;0m')
      print(encryptedMessage) 
    
    # -------------------------------- task 3 --------------------------------
    if task_num == 3:
      message = input("Please type in your encrypted message: ")
      
      message = message.replace("[", "")
      message = message.replace("]", "")
      message = message.replace(" ", "")
      message = message.split(",")
      message = list(map(int, message))
      print(message)

      # tell board to decrypt message
      num = 3000
      st = f"{num:04d}"
      ser.write(st.encode('utf-8'))

      # send board the message len
      ser.write(len(message).to_bytes(1, 'little'))
      received = ser.read(1)

      # send board message
      for c in message:
        ser.write(c.to_bytes(1, 'little'))
        received = ser.read(1)
      
      # recive decrypted message and output it
      key = ser.readline()
      print('\033[2;30;43m Your Decrypted Message is: \033[0;0m')
      print(str(key)) 


