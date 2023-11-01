from hashlib import sha256
import unittest

def sha256prefix(s, hex_len=16):
    return sha256(s.encode()).hexdigest()[:hex_len]

class TestCollisions(unittest.TestCase):
    def test1(self):
        self.assertEqual(
            sha256prefix('08RTz8'),
            sha256prefix('4iRDWF'))

    def test2(self):
        self.assertEqual(
            sha256prefix('000000', hex_len=2),
            sha256prefix('zzzzzz', hex_len=2))

if __name__ == '__main__':
    unittest.main()
