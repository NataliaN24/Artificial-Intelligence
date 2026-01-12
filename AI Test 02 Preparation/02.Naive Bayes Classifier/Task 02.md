Goal

Implement a categorical Naive Bayes classifier that predicts Spam or Ham using only 1 attribute:

contains_free ∈ {y, n}

class ∈ {spam, ham}

Dataset (8 rows)

Hardcode this data in the program:

y spam
y spam
y spam
n spam
n ham
n ham
n ham
y ham

Test input

User enters one value:

y


or

n

Output

Print:

score for spam

score for ham

predicted class

Requirements

Use counts to compute probabilities:

Prior: P(Class)

Likelihood: P(free=y | Class), P(free=n | Class)
