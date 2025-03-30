import random
import string

def string_generator(lg):
    return ''.join(random.choice(string.ascii_uppercase) for _ in range(lg))
