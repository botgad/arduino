#include &lt;DHT.h&gt;
int DHpin = 8; // Pin numérique connectée au capteur DHT
byte dat[5]; // Tableau pour stocker les 5 octets envoyés par le capteur
byte read_data() {
    byte data = 0;   // OBLIGATOIRE et initialise l&#39;octet à 0
    for (int i = 0; i &lt; 8; i++) {
        while (digitalRead(DHpin) == LOW);  Attend que le signal passe HIGH
(début du bit)
        delayMicroseconds(30); // Petit délai pour synchroniser la lecture
        if (digitalRead(DHpin) == HIGH) //Si le signal est HIGH, on considère
le bit comme 1

            data |= (1 &lt;&lt; (7 - i)); // On place le bit à sa position dans
l&#39;octet
        while (digitalRead(DHpin) == HIGH);  // attendre la fin du bit (retour
à low)
    }
    return data;
}
void start_test() {
    // signal de départ
    pinMode(DHpin, OUTPUT);
    digitalWrite(DHpin, LOW); // Envoie un signal bas pour initier la
communication
    delay(30);
    digitalWrite(DHpin, HIGH); // Remonte le signal
    delayMicroseconds(40);
    pinMode(DHpin, INPUT); // Passe le pin en entrée pour recevoir les données
du capteur
    // réponse du capteur
    while (digitalRead(DHpin) == HIGH);
    delayMicroseconds(80);
    while (digitalRead(DHpin) == LOW);
    delayMicroseconds(80);
    // Lecture des 5 octets envoyés par le DHT
    for (int i = 0; i &lt; 5; i++)
        dat[i] = read_data();
    // Fin de la communication : remettre la pin en HIGH
    pinMode(DHpin, OUTPUT);
    digitalWrite(DHpin, HIGH);
}
void setup() {
    Serial.begin(9600); // Initialise la communication série pour afficher les
résultats
}
void loop() {
    start_test();
    // vérification checksum (pour afficher correctement nos valeurs)
    if (dat[4] != (dat[0] + dat[1] + dat[2] + dat[3])) {
        Serial.println(&quot;Erreur checksum&quot;);
        delay(1000);
        return;
    }

// affichage des valeurs : la partie entière+décimal
    Serial.print(&quot;Current humidity = &quot;);
    Serial.print(dat[0]);
    Serial.print(&quot;.&quot;);
    Serial.print(dat[1]);
    Serial.println(&quot; %&quot;);
    Serial.print(&quot;Current temperature = &quot;);
    Serial.print(dat[2]);
    Serial.print(&quot;.&quot;);
    Serial.print(dat[3]);
    Serial.println(&quot; C&quot;);
    delay(1000);
}