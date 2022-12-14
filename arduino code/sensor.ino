
String BT_input; // to store input character received via BT.
const int LED = 13;
const int Trigger = 2; // Pin digital 2 para el Trigger del sensor
const int Echo = 3;    // Pin digital 3 para el echo del sensor
int distanciaPeligro = 50;
const int pinBuzzer = 5;
void setup()
{
    Serial.begin(9600); // default baud rate of module
    pinMode(LED, OUTPUT);
    pinMode(Trigger, OUTPUT);   // pin como salida
    pinMode(Echo, INPUT);       // pin como entrada
    digitalWrite(Trigger, LOW); // Inicializamos el pin con 0
    while (!Serial)
    {
        // wait for serial port to connect. Needed for native USB port only
    }
}

void loop()

{
    if (Serial.available())
    {
        BT_input = Serial.readString(); // read input string from bluetooth
        if (isNumeric(BT_input))
        {
            distanciaPeligro = BT_input.toInt();
            Serial.print("Nueva distancia de peligro: ");
            Serial.print(BT_input);
            Serial.println();
        }
    }
    long t; // timepo que demora en llegar el eco
    long d; // distancia en centimetros

    digitalWrite(Trigger, HIGH);
    delayMicroseconds(10); // Enviamos un pulso de 10us
    digitalWrite(Trigger, LOW);

    t = pulseIn(Echo, HIGH); // obtenemos el ancho del pulso
    d = t / 59;

    if (d < distanciaPeligro)
    {
        digitalWrite(LED, HIGH);
        tone(pinBuzzer, 10);
        Serial.print("PELIGRO!: ");
        Serial.print(d); // Enviamos serialmente el valor de la distancia
        Serial.print("cm");
        Serial.println();
    }
    else
    {
        noTone(pinBuzzer);
        digitalWrite(LED, LOW);
    }

    delay(500); // Hacemos una pausa de 100ms
}

boolean isNumeric(String str)
{
    unsigned int stringLength = str.length();

    if (stringLength == 0)
    {
        return false;
    }

    boolean seenDecimal = false;

    for (unsigned int i = 0; i < stringLength; ++i)
    {
        if (isDigit(str.charAt(i)))
        {
            continue;
        }

        if (str.charAt(i) == '.')
        {
            if (seenDecimal)
            {
                return false;
            }
            seenDecimal = true;
            continue;
        }
        return false;
    }
    return true;
}
