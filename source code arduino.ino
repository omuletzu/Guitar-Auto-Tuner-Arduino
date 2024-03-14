#include <arduinoFFT.h>
#include <uspeech.h>
#include <Servo.h>

#define pin_voce A0
#define pin_vibrat A2
#define pin_servo 9

#define pin_buton 12
bool buton_debouncer_string = false;

#define led_reset_warning 10
#define led_on_off 13
#define led_vibrat 8

#define pin_buton_change_tuning A4
bool buton_debouncer_change_tuning = false;
bool buton_debouncer = false;
bool tuning_mode = false;

#define led_tuning_mode A5
#define led_stringE1 2
#define led_stringA 3
#define led_stringD 4
#define led_stringG 5
#define led_stringB 6
#define led_stringE2 7
#define led_finish_tune 11
int actual_led_string = 0;

#define FFT_SAMPLES 128
#define FFT_FREQ 1000

int queue_freq[5];

unsigned int sampling_period_us;
unsigned long microseconds;

arduinoFFT FFT;

bool detect_freq_on_off = false;
int freq_media_suma = 0;
int freq_media_contor = 0;

int string_E1;
int string_A;
int string_D;
int string_G;
int string_B;
int string_E2;

Servo motor;

signal voice(pin_voce);
String collvoice;
char prev;
boolean newline = false;
int sum = 0;

void setup() {

  sampling_period_us = round(1000000 * (1.0 / FFT_FREQ));

  Serial.begin(9600);

  pinMode(pin_buton, INPUT);
  pinMode(pin_servo, OUTPUT);

  pinMode(led_vibrat, OUTPUT);
  pinMode(led_on_off, OUTPUT);
  pinMode(led_reset_warning, OUTPUT);

  pinMode(pin_buton_change_tuning, INPUT);
  pinMode(led_tuning_mode, OUTPUT);

  pinMode(led_stringE1, OUTPUT);
  pinMode(led_stringA, OUTPUT);
  pinMode(led_stringD, OUTPUT);
  pinMode(led_stringG, OUTPUT);
  pinMode(led_stringB, OUTPUT);
  pinMode(led_stringE2, OUTPUT);
  pinMode(led_finish_tune, OUTPUT);

  voice.f_enabled = true;
  voice.minVolume = 500;
  voice.fconstant = 750;
  voice.econstant = 1;
  voice.aconstant = 2;
  voice.vconstant = 3;
  voice.shconstant = 4;
  voice.calibrate();
  Serial.begin(9600);

  motor.attach(9);
  motor.write(90);
  delay(10);
}

void loop() {

  voice.sample();  ////  VOCE

  char p = voice.getPhoneme();

  if (p != ' ') {

    if (p == 's') {
      newline = true;

      change_string_led();
      digitalWrite(led_tuning_mode, LOW);

      string_E1 = 82;
      string_A = 110;
      string_D = 147;
      string_G = 196;
      string_B = 247;
      string_E2 = 330;
    }

    if (p == 'o') {
      newline = false;
      actual_led_string = 0;

      stop_all_button_leds();

      motor.write(90);
      delay(10);
    }
  } else {

    if (newline)
      digitalWrite(led_on_off, HIGH);
    else
      digitalWrite(led_on_off, LOW);
  }  //// VOCE

  if (newline) {

    microseconds = micros();  //// FFT

    double vReal[FFT_SAMPLES];
    double vImag[FFT_SAMPLES];

    for (int i = 0; i < FFT_SAMPLES; i++) {
      vReal[i] = analogRead(pin_vibrat);  //// SAMPLES VIBRATII
      vImag[i] = 0;

      while (micros() - microseconds < sampling_period_us) {
      }
      microseconds += sampling_period_us;

      if (vReal[i] > 10)
        digitalWrite(led_vibrat, HIGH);
      else
        digitalWrite(led_vibrat, LOW);
    }

    int button_mode = digitalRead(pin_buton);

    if (button_mode == HIGH && !buton_debouncer) {
      change_string_led();
      digitalWrite(led_finish_tune, LOW);
      buton_debouncer = true;
    }

    int button_change_tuning = digitalRead(pin_buton_change_tuning);

    if (button_change_tuning == HIGH && !buton_debouncer_change_tuning) {

      if (!tuning_mode) {

        string_E1 = 73;                // DOUBLE DROP D TUNING D A D F# B D
        string_A = 110;
        string_D = 146;
        string_G = 185;
        string_B = 246;
        string_E2 = 293;
        tuning_mode = true;

        digitalWrite(led_tuning_mode, HIGH);
      }
      else{

        string_E1 = 82;                   // STANDARD TUNING E A D G B E
        string_A = 110;
        string_D = 146;
        string_G = 196;
        string_B = 246;
        string_E2 = 330;
        tuning_mode = false;

        digitalWrite(led_tuning_mode, LOW);
      }

      buton_debouncer_change_tuning = true;
    }

    if (!button_mode)
      buton_debouncer = false;

    if (!button_change_tuning)
      buton_debouncer_change_tuning = false;

    FFT = arduinoFFT(vReal, vImag, FFT_SAMPLES, FFT_FREQ);

    FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);

    FFT.Compute(FFT_FORWARD);

    FFT.ComplexToMagnitude();

    const int freq = FFT.MajorPeak();  //// REZULTAT FFT (FRECVENTA)

    //if(freq_in_interval(freq)){
    //Serial.println(freq);                                                         //// AFISARE FRECVENTA
    //}

    shift_in_queue(freq);

    if (freq_in_interval(freq) && signal_on()) {  //// INCEPUT DE SEMNAL

      detect_freq_on_off = true;
      freq_media_suma += freq;
      freq_media_contor++;
    } else {

      if (detect_freq_on_off) {  //// INCHEIERE SEMNAL

        const int freq_finala = freq_media_suma / freq_media_contor;  //// FRECVENTA FINALA

        Serial.print(freq_finala);
        Serial.print(" ");

        tune_string(freq_finala);

        detect_freq_on_off = false;
        freq_media_suma = 0;
        freq_media_contor = 0;
      }
    }
  }
}

void tune_string(int freq_finala) {

  int sensitivity = 6;
  int error;

  if (actual_led_string == 1) {
    error = string_E1 - freq_finala;
  }

  if (actual_led_string == 2) {
    error = string_A - freq_finala;
  }

  if (actual_led_string == 3) {
    error = string_D - freq_finala;
  }

  if (actual_led_string == 4) {
    error = string_G - freq_finala;
  }

  if (actual_led_string == 5) {
    error = string_B - freq_finala;
  }

  if (actual_led_string == 6) {
    error = string_E2 - freq_finala;
  }

  Serial.println(abs(error));

  if (abs(error) > 100) {
    Serial.println("Out of range");
    return;
  }

  if (abs(error) < 4) {
    blink_led(led_finish_tune, false);
    digitalWrite(led_finish_tune, HIGH);
  } else {
    digitalWrite(led_finish_tune, LOW);
  }

  if (abs(error) > 1) {

    motor.write(motor.read() - sensitivity * error);
    delay(10);

    if (motor.read() == 180) {
      reset_servo(25);
    }

    if(motor.read() == 0){
      reset_servo(165);
    }
  }
}

void reset_servo(int degree) {

  blink_led(led_reset_warning, true);

  motor.write(degree);
}

void change_string_led() {

  motor.write(90);
  delay(10);

  switch (actual_led_string) {

    case 0:
      actual_led_string = 1;
      stop_all_button_leds();
      digitalWrite(led_stringE1, HIGH);
      break;

    case 1:
      actual_led_string = 2;
      digitalWrite(led_stringA, HIGH);
      digitalWrite(led_stringE1, LOW);
      break;

    case 2:
      actual_led_string = 3;
      digitalWrite(led_stringD, HIGH);
      digitalWrite(led_stringA, LOW);
      break;

    case 3:
      actual_led_string = 4;
      digitalWrite(led_stringG, HIGH);
      digitalWrite(led_stringD, LOW);
      break;

    case 4:
      actual_led_string = 5;
      digitalWrite(led_stringB, HIGH);
      digitalWrite(led_stringG, LOW);
      break;

    case 5:
      actual_led_string = 6;
      digitalWrite(led_stringE2, HIGH);
      digitalWrite(led_stringB, LOW);
      break;

    case 6:
      actual_led_string = 1;
      digitalWrite(led_stringE1, HIGH);
      digitalWrite(led_stringE2, LOW);
      break;
  }
}

void stop_all_button_leds() {

  digitalWrite(led_stringE1, LOW);
  digitalWrite(led_stringA, LOW);
  digitalWrite(led_stringD, LOW);
  digitalWrite(led_stringG, LOW);
  digitalWrite(led_stringB, LOW);
  digitalWrite(led_stringE2, LOW);

  digitalWrite(led_finish_tune, LOW);
  digitalWrite(led_vibrat, LOW);
  digitalWrite(led_tuning_mode, LOW);
}

void shift_in_queue(int freq) {
  queue_freq[4] = queue_freq[3];
  queue_freq[3] = queue_freq[2];
  queue_freq[2] = queue_freq[1];
  queue_freq[1] = queue_freq[0];
  queue_freq[0] = freq;
}

void blink_led(int led, bool delay_on_off) {

  digitalWrite(led, HIGH);
  delay(250);
  digitalWrite(led, LOW);
  delay(250);
  digitalWrite(led, HIGH);

  if (delay_on_off)
    delay(2000);

  digitalWrite(led, LOW);
}

bool signal_on() {
  return abs(queue_freq[1] - queue_freq[0]) < 5 && abs(queue_freq[2] - queue_freq[1]) < 5 && abs(queue_freq[3] - queue_freq[2]) < 5 && abs(queue_freq[4] - queue_freq[3]) < 5;
}

bool freq_in_interval(int freq) {
  return freq >= 55 && freq < 400;
}