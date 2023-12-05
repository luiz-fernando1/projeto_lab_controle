clc
clear all
close all

load dados_result.M
id = dados_result;

sp = id(:,3); % valores de entrada 
sensor = id(:,4); % valores de saída 
e=  id(:,5);

zero=zeros(398,1);

figure(2)
plot(zero);               
hold on
plot(e);
title('Erro relativo a altura')



figure(1)
plot(sp);               
hold on
plot(sensor);
title('Relação Setpont x Altura lida')
legend('SetPoint','Altura da Bola');
