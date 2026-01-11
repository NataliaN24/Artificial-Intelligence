1) Идеята на kNN (как да го мислиш)

kNN е supervised learning метод за:

класификация (клас е дискретен: “Cold/Mild/Hot”, “Spam/Ham”)

регресия (изходът е число: температура, цена и т.н.)

Ключът: няма “истинско” обучение като при дървета/невронни мрежи.
Той е instance-based / lazy learning: просто пазиш тренировъчните примери и чак когато дойде нова точка 
​, търсиш най-близките примери до нея и “гласуваш”. 

<img width="1048" height="412" alt="image" src="https://github.com/user-attachments/assets/4deeb86d-cef5-4490-bd29-aa10ce7e5e2b" />
<img width="1077" height="397" alt="image" src="https://github.com/user-attachments/assets/2f74e199-66c8-4a5e-9d96-8e097891f4b3" />
