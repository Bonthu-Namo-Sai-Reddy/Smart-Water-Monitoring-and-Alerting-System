#define TdsSensorPin A0
#define VREF 5.0
#define SCOUNT 30

int analogBuffer[SCOUNT];
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0;
int copyIndex = 0;

float averageVoltage = 0;
float tdsValue = 0;
float temperature = 25;

unsigned long analogSampleTimepoint = 0;
unsigned long displayUpdateTimepoint = 0;
const unsigned long displayUpdateInterval = 1000; // Update the display every 1 second

void setup() {
  Serial.begin(9600);
  pinMode(TdsSensorPin, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  // Update TDS value if enough time has passed
  if (currentMillis - analogSampleTimepoint > 40U) {
    analogSampleTimepoint = currentMillis;
    analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);
    analogBufferIndex = (analogBufferIndex + 1) % SCOUNT;
  }

  // Calculate TDS value only when it's time to update the serial monitor
  if (currentMillis - displayUpdateTimepoint >= displayUpdateInterval) {
    displayUpdateTimepoint = currentMillis;

    for (copyIndex = 0; copyIndex < SCOUNT; copyIndex++) {
      analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
    }

    averageVoltage = getMedianNum(analogBufferTemp, SCOUNT) * (float)VREF / 1024.0;
    float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);
    float compensationVoltage = averageVoltage / compensationCoefficient;
    float newTdsValue = (133.42 * compensationVoltage * compensationVoltage * compensationVoltage - 255.86 * compensationVoltage * compensationVoltage + 857.39 * compensationVoltage) * 0.5;

    // Display TDS value in the serial monitor
    Serial.print("TDS Value: ");
    Serial.println(newTdsValue);
  }
}

int getMedianNum(int bArray[], int iFilterLen) {
  int bTab[iFilterLen];
  for (int i = 0; i < iFilterLen; i++) {
    bTab[i] = bArray[i];
  }

  int i, j, bTemp;
  for (j = 0; j < iFilterLen - 1; j++) {
    for (i = 0; i < iFilterLen - j - 1; i++) {
      if (bTab[i] > bTab[i + 1]) {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }

  if (iFilterLen & 1) {
    bTemp = bTab[iFilterLen / 2];
  } else {
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  }
  return bTemp;
}
