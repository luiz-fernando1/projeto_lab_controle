clc
clear all
close all

load dados1.M
id = dados1;

in = id(:,1); % valores de entrada 
out = id(:,2); % valores de saída 
t = id(:,3)/1000; % tempo em segundos (Ts =0.02s)

figure(1)
plot(t,out)

figure(2)
subplot(2,1,1);
plot(t,in);               
title('Sinal entrada')
legend('PWM')

subplot(2,1,2);
plot(t, out);
title('Sinal de saída');
legend('Altura da Bola');

% Identifcação do sistema
ident

s = tf('s');

%Process Model

% 1
Kp1=0.20177;
Tp1=3.0287;
Tp11=2.9389;
Td1=0.2625;
H1 = Kp1*exp(-Td1*s)/((1+Tp1*s)*(1+Tp11*s))

step(H1)

% 2
Kp2=0.22778;
Tp2=3.3307;
Tp22=3.1219;
Td2=0.6;
H2 = Kp2*exp(-Td2*s)/((1+Tp2*s)*(1+Tp22*s))

step(H2)

% 3
Kp3=-0.58967;
Tp3=11.2185;
Td3= 0.6;
H3 = Kp3*exp(-Td3*s)/(1+Tp3*s)


Kpm = (Kp1+Kp2)/2;
Tpm = (Tp1+Tp2)/2;
Tdm = (Td1+Td2)/2;

G1 = Kpm*exp(-Tdm*s)/(1+Tpm*s)

%sisotool(H1)

pidtool(H2)

step(G1)






% figure()
% subplot(2,1,1);
% plot(t(1:200), in(1:200), 'r', t(201:500), in(201:500), 'b',  t(501:700), in(501:700),  t(701:end), in(701:end), 'm');               
% title('Sinal entrada')
% legend('PWM')
% 
% subplot(2,1,2);
% plot(t(1:200), out(1:200), 'r', t(201:500), out(201:500), 'b', t(501:700), out(501:700), t(701:end), out(701:end), 'm');
% title('Sinal de saída');
% legend('Altura da Bola')

