Задача 2: kNN с N-Fold Cross-Validation

Цел: Да разбереш overfitting / generalization

Изисквания:

Раздели данните на N folds

За всеки fold:

тренирай върху N-1

тествай върху 1

Изчисли Accuracy за всеки fold

Изчисли средна Accuracy


Какво означава N-Fold Cross-Validation

Имаш dataset с M примера.

Разделяш ги на N приблизително равни части → folds

Правиш N експеримента

Всеки път:

1 fold = test set

останалите N-1 folds = training set

Мериш Accuracy

Накрая взимаш средната Accuracy
