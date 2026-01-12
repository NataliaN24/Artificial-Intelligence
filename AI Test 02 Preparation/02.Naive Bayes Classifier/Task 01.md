Task 1 — Basic Categorical Naive Bayes (hardcoded dataset)

Цел: да имплементираш NBC за категорийни атрибути (без вход от потребител).

Изисквания:

dataset = vector от редове: (Outlook, Temp, Humidity, Wind, Class)

изчисли:

priors P(Class)

likelihoods P(feature=value | Class)

classify 1 test sample

изведи:

score за всеки клас

избрания клас
<img width="1162" height="678" alt="image" src="https://github.com/user-attachments/assets/50938a2c-da73-4326-870b-71b87e7b0b05" />
Outlook   Temp   Humidity   Wind     Class
Sunny     Hot    High       Weak     No
Sunny     Hot    High       Strong   No
Overcast  Hot    High       Weak     Yes
Rain      Mild   High       Weak     Yes
Rain      Cool   Normal     Weak     Yes
Rain      Cool   Normal     Strong   No
Overcast  Cool   Normal     Strong   Yes
Sunny     Mild   High       Weak     No
Sunny     Cool   Normal     Weak     Yes
Rain      Mild   Normal     Weak     Yes
Sunny     Mild   Normal     Strong   Yes
Overcast  Mild   High       Strong   Yes
Overcast  Hot    Normal     Weak     Yes
Rain      Mild   High       Strong   No
Тестов пример:

Sunny Cool High Strong
