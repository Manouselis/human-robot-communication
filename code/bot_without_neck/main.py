from __future__ import division

import re
import sys

from google.cloud import speech

import os
os.environ["GOOGLE_APPLICATION_CREDENTIALS"]="/Users/mihnea-adrian/PycharmProjects/hrc/key.json"

import pyaudio
from six.moves import queue

# Audio recording parameters
RATE = 16000
CHUNK = int(RATE / 10)  # 100ms


class MicrophoneStream(object):
    """Opens a recording stream as a generator yielding the audio chunks."""

    def __init__(self, rate, chunk):
        self._rate = rate
        self._chunk = chunk

        # Create a thread-safe buffer of audio data
        self._buff = queue.Queue()
        self.closed = True

    def __enter__(self):
        self._audio_interface = pyaudio.PyAudio()
        self._audio_stream = self._audio_interface.open(
            format=pyaudio.paInt16,
            # The API currently only supports 1-channel (mono) audio
            # https://goo.gl/z757pE
            channels=1,
            rate=self._rate,
            input=True,
            frames_per_buffer=self._chunk,
            # Run the audio stream asynchronously to fill the buffer object.
            # This is necessary so that the input device's buffer doesn't
            # overflow while the calling thread makes network requests, etc.
            stream_callback=self._fill_buffer,
        )

        self.closed = False

        return self

    def __exit__(self, type, value, traceback):
        self._audio_stream.stop_stream()
        self._audio_stream.close()
        self.closed = True
        # Signal the generator to terminate so that the client's
        # streaming_recognize method will not block the process termination.
        self._buff.put(None)
        self._audio_interface.terminate()

    def _fill_buffer(self, in_data, frame_count, time_info, status_flags):
        """Continuously collect data from the audio stream, into the buffer."""
        self._buff.put(in_data)
        return None, pyaudio.paContinue

    def generator(self):
        while not self.closed:
            # Use a blocking get() to ensure there's at least one chunk of
            # data, and stop iteration if the chunk is None, indicating the
            # end of the audio stream.
            chunk = self._buff.get()
            if chunk is None:
                return
            data = [chunk]

            # Now consume whatever other data's still buffered.
            while True:
                try:
                    chunk = self._buff.get(block=False)
                    if chunk is None:
                        return
                    data.append(chunk)
                except queue.Empty:
                    break

            yield b"".join(data)


def listen_print_loop(responses):
    global conversation

    """Iterates through server responses and prints them.

    The responses passed is a generator that will block until a response
    is provided by the server.

    Each response may contain multiple results, and each result may contain
    multiple alternatives; for details, see https://goo.gl/tjCPAU.  Here we
    print only the transcription for the top alternative of the top result.

    In this case, responses are provided for interim results as well. If the
    response is an interim one, print a line feed at the end of it, to allow
    the next result to overwrite it, until the response is a final one. For the
    final one, print a newline to preserve the finalized transcription.
    """
    num_chars_printed = 0
    for response in responses:
        if not response.results:
            continue

        # The `results` list is consecutive. For streaming, we only care about
        # the first result being considered, since once it's `is_final`, it
        # moves on to considering the next utterance.
        result = response.results[0]
        if not result.alternatives:
            continue

        # Display the transcription of the top alternative.
        transcript = result.alternatives[0].transcript

        # Display interim results, but with a carriage return at the end of the
        # line, so subsequent lines will overwrite them.
        #
        # If the previous result was longer than this one, we need to print
        # some extra spaces to overwrite the previous result
        overwrite_chars = " " * (num_chars_printed - len(transcript))

        if not result.is_final:
            sys.stdout.write(transcript + overwrite_chars + "\r")
            sys.stdout.flush()

            num_chars_printed = len(transcript)

        else:
            print(transcript + overwrite_chars)

            analyze_transcript(transcript)

            # Exit recognition if any of the transcribed phrases could be
            # one of our keywords.
            if re.search(r"\b(exit|quit)\b", transcript, re.I):
                print("Exiting..")
                break

            num_chars_printed = 0

import serial
import time

face_in_front = False


def camera_input():
    global conversation
    global face_in_front
    while True:
        time.sleep(1)
        faceinfo = arduino.readline()
        print(faceinfo)
        if b'face detected\r\n' == faceinfo and conversation == 0 and face_in_front == False:
            print("face detected, greetingplay")
            conversation = 1
            face_in_front = True
            write_read("s-greeting")
        elif face_in_front and b'face is gone\r\n' == faceinfo:
            print("face gone, goodbye")
            conversation = 0
            face_in_front = False
            write_read("s-goodbye")


arduino = serial.Serial(port="/dev/cu.usbmodem11301", baudrate=115200, timeout=.1)


def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return data


conversation = 0 # conversation not started
wait_for_user = False


def analyze_transcript(transcript):
    global conversation
    global face_in_front
    global wait_for_user
    global last_user_choice
    global last_bo_choice
    global last_state_game
    global needs_update
    transcript = transcript.lower()
    if face_in_front:
        text = df(transcript).lower()
        command = "s-" + text
        if conversation == 0:
            print("human started conversation")
            last_user_choice = ""
            last_bo_choice = ""
            last_state_game = ""
            needs_update = False
            conversation = 1
        elif conversation == 1:
            if wait_for_user:
                if text == "rock" or text == "paper" or text == "scissors":
                    print(command)
                    check_game(text)
                else:
                    write_read("s-robotmad")
                wait_for_user = False
            else:
                if text == "countdown" or text == "groundrules":
                    wait_for_user = True
                elif text == "goodbye":
                    conversation = 0
                print(command)
                write_read(command)
    else:
        conversation = 0
        print('no face')


import random


last_user_choice = ""
last_bo_choice = ""
last_state_game = ""

rps_dict = {"scissors": "rock", "rock": "paper", "paper": "scissors"}


def check_game(user_choice):
    global last_state_game
    global last_bo_choice
    global last_user_choice
    global needs_update

    if last_state_game == "robotlose":
        bo_choice = rps_dict.get(last_user_choice)
    elif last_state_game == "robotwins":
        bo_choice = last_user_choice
    else:
        bo_choice = random.choice(list(rps_dict.values()))

    print(bo_choice)
    write_read("s-" + bo_choice)

    if bo_choice == rps_dict.get(user_choice):
        last_state_game = "robotwins"
    elif rps_dict.get(bo_choice) == user_choice:
        last_state_game = "robotlose"
    elif bo_choice == user_choice:
        last_state_game = "robottie"
    else:
        last_state_game = "robotmad"

    last_bo_choice = bo_choice
    last_user_choice = user_choice

    time.sleep(0.2)

    needs_update = True


needs_update = False


def update_state_game():
    global last_state_game
    global needs_update
    while True:
        time.sleep(1.3)
        if needs_update:
            time.sleep(0.5)
            print(last_state_game)
            write_read("s-" + last_state_game)
            needs_update = False


def audio_stream():

    # See http://g.co/cloud/speech/docs/languages
    # for a list of supported languages.
    language_code = "en-US"  # a BCP-47 language tag

    client = speech.SpeechClient()
    config = speech.RecognitionConfig(
        encoding=speech.RecognitionConfig.AudioEncoding.LINEAR16,
        sample_rate_hertz=RATE,
        language_code=language_code,
    )

    streaming_config = speech.StreamingRecognitionConfig(
        config=config, interim_results=True
    )

    with MicrophoneStream(RATE, CHUNK) as stream:
        audio_generator = stream.generator()
        requests = (
            speech.StreamingRecognizeRequest(audio_content=content)
            for content in audio_generator
        )

        responses = client.streaming_recognize(streaming_config, requests)

        print(responses)

        # Now, put the transcription responses to use.
        listen_print_loop(responses)

"""Install the following requirements:
    dialogflow        0.5.1
    google-api-core   1.4.1
"""
import os
from google.cloud import dialogflow_v2beta1 as dialogflow
from google.api_core.exceptions import InvalidArgument

os.environ["GOOGLE_APPLICATION_CREDENTIALS"] = 'bothebox-vbff-44c2db288a62.json'

DIALOGFLOW_PROJECT_ID = 'bothebox-vbff'
DIALOGFLOW_LANGUAGE_CODE = 'en'
SESSION_ID = 'me'

session_client = dialogflow.SessionsClient()
session = session_client.session_path(DIALOGFLOW_PROJECT_ID, SESSION_ID)


def df(text_to_be_analyzed):
    print(text_to_be_analyzed)
    text_input = dialogflow.types.TextInput(text=str(text_to_be_analyzed), language_code=DIALOGFLOW_LANGUAGE_CODE)
    query_input = dialogflow.types.QueryInput(text=text_input)
    try:
        response = session_client.detect_intent(session=session, query_input=query_input)
    except InvalidArgument:
        raise

    # print("Query text:", response.query_result.query_text)
    print("Detected intent:", response.query_result.intent.display_name)
    # print("Detected intent confidence:", response.query_result.intent_detection_confidence)
    print("Fulfillment text:", response.query_result.fulfillment_text)

    s = response.query_result.fulfillment_text
    return s[s.find("(")+1:s.find(")")]


from threading import Thread

if __name__ == '__main__':
    Thread(target = camera_input).start()
    Thread(target=update_state_game).start()
    Thread(target=audio_stream).start()

