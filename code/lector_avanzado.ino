// Function prototypes
// - specify default values here
bool takeAnalogReadings(uint16_t* p_numReadings = nullptr, uint16_t** p_analogVals = nullptr);

void setup()
{
  Serial.begin(115200);
  Serial.println("\nBegin\n");
}

void loop()
{
  // This is one way to just take readings
  // takeAnalogReadings();

  // This is a way to both take readings *and* read out the values when the buffer is full
  uint16_t numReadings;
  uint16_t* analogVals;
  bool readingsDone = takeAnalogReadings(&numReadings, &analogVals);
  if (readingsDone)
  {
    // Let's print them all out!
    //Serial.print("numReadings = "); Serial.println(numReadings);
    Serial.print("[");
    for (uint16_t i=0; i<numReadings; i++)
    {
      if (i!=0)
      {
        Serial.print(", ");
      }
       Serial.print(analogVals[i]);
    }
    Serial.println("]");
  }
}

// Function definitions:

//---------------------------------------------------------------------------------------------------------------------
// Take analog readings to fill up a buffer.
// Once the buffer is full, return true so that the caller can read out the data.
// Optionally pass in a pointer to get access to the internal buffer in order to read out the data from outside
// this function.
//---------------------------------------------------------------------------------------------------------------------
bool takeAnalogReadings(uint16_t* p_numReadings, uint16_t** p_analogVals)
{
  static const uint16_t NUM_READINGS = 70;
  static uint16_t i = 0; // index
  static uint16_t analogVals[NUM_READINGS];

  const uint32_t SAMPLE_PD = 1; // us; sample period (how often to take a new sample)
  static uint32_t tStart = micros(); // us; start time
  bool bufferIsFull = false; // set to true each time NUM_READINGS have been taken

  // Only take a reading once per SAMPLE_PD
  uint32_t tNow = micros(); // us; time now
  if (tNow - tStart >= SAMPLE_PD)
  {
    //Serial.print("taking sample num "); Serial.println(i + 1);
    tStart += SAMPLE_PD; // reset start time to take next sample at exactly the correct pd
    analogVals[i] = analogRead(A0);
    i++;
    if (i >= NUM_READINGS)
    {
      bufferIsFull = true;
      i = 0; // reset to beginning of array, so you don't try to save readings outside of the bounds of the array
    }
  }

  // Assign the user-passed-in pointers so that the user can retrieve the data if they so desire to do it this way
  if (p_numReadings != nullptr)
  {
    *p_numReadings = NUM_READINGS;
  }
  if (p_analogVals != nullptr)
  {
    *p_analogVals = analogVals;
  }

  return bufferIsFull;
}
