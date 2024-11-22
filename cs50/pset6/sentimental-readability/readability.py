from cs50 import get_string
import re

text = get_string("Text: ")
words = re.findall("\S+", text)
letters = re.findall("[A-Za-z]", text)
sentences = re.findall("[.|!|?]", text)


print(f"{len(letters)} letters")
print(f"{len(words)} words")
print(f"{len(sentences)} sentences")

L = (float(len(letters)) / float(len(words))) * 100.0
S = (float(len(sentences)) / float(len(words))) * 100.0
index = 0.0588 * L - 0.296 * S - 15.8
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {round(index)}")
