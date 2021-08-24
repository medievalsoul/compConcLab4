### LAB4

Aluno: Jonathan Suhett Barbêdo                                 DRE: 120021182



**Atividade 1**

Executando o programa diversas vezes, podemos ver que algumas coisas acontecem em ordem diferente, mas a condição lógica do programa é sempre obedecida, que é fazer com que os dois HELLO sejam impressos antes do BYE.

As coisas que podem ocorrer fora de ordem são: thread A e B começarem em ordens diferentes. Thread A pode inclusive imprimir "HELLO" antes da B começar. Porém, as últimas linhas sempre serão iguais.

``` 
A:  x = 2, vai sinalizar a condicao
B: sinal recebido e mutex realocado, x = 2
BYE

FIM
```

O que teoricamente também é possível de acontecer é as threads A incrementarem x antes de B se bloquear. Dessa forma, a linha  `B: x= 0, vai se bloquear...` não seria impressa.  Mas por conta do  tempo gasto em`while (boba2 < boba1) boba2++;`   a thread B se bloqueou em todas as vezes que eu rodei o programa.

Ao alterar o númerno de threads para 1, o programa cai em um deadlock. Pois o valor de x nunca será incrementado para 2, e portanto a thread B nunca será desbloqueada.

Ao criar uma segunda thread B, na maior parte das minhas execuções eu caí em uma situaçãode deadlock. Isso ocorreu, pois as duas threads B  haviam se bloqueado e apenas um signal é emitido pelas threads A, fazendo com que a segunda thread B nunca saia do estado de espera. Para que não haja o deadlock, pelo menos uma das threads B não pode estar bloqueada no momento em que x=2.



**Atividade 2**

O resultado foi sempre o esperado. As execuções que ocorreram em ordem diferente eram independentes. O importante foi que os BYEs foram impressos depois do HELLO, devido ao broadcast, que sinalizou para as duas threads saírem da espera.



**Atividade 3**

O log de execução foi sempre correta. Os valores de A e B foram sempre impressos quando x era múltiplo de 10. Nas minhas execuções do programa, tiveram dois casos mais comuns. No primeiro B entrava na seção crítica com valor de x inválido e era bloqueado. Dessa forma, imprimia sempre o valor 40, após as outras threads já terem finalizado os seus processos. No segundo caso, devido ao trecho de código  `while (boba2 < boba1) boba2++;` a thread B conseguia tempo para começar a executar sem que o valor de x fosse alterado, imprimindo x=20. Os casos onde x=0 e x=30 ocorreram mais raramente. O caso onde x=10 não ocorreu nenhuma vez.

A linha 50 não pode ser substituída pela 51, pois a avaliação não pode ser feita apenas uma vez. Quando a thread B recebe o signal, pode ser que o valor de x seja alterado antes que ela consiga utilizar o lock, e portanto, o valor de x não seria impresso corretamente.

Como previsto, ao comentar a linha 50 e descomentar a 51, o processo não ocorreu sempre da maneira planejada. Na maior parte das vezes, o valor de x era múltiplo de 10. Porém após algumas execuções (22, no meu caso) o valor de x impresso não é um múltiplo de 10.
