clear;
close all;
clc;

%% Continuous plant
Tr = 7.01;
K  = 0.17;
Ts = 0.002;

Gc = tf(K,[Tr 1 0]);

%% Dicretize the plant (ZOH)
Gd = c2d(Gc,Ts,'zoh');

disp('Discrete plant:')
Gd

[num,den] = tfdata(Gd,'v');

A = den;
B = num;

%% Desired transient response

PeakTime = 2.5;
OS = 2.5;

zeta = -log(OS/100)/sqrt(pi^2+log(OS/100)^2);
wn = pi/(PeakTime*sqrt(1-zeta^2));

sigma = -zeta*wn;
wd = wn*sqrt(1-zeta^2);

%% Desired poles in z-plane

p1 = sigma + 1i*wd;
p2 = sigma - 1i*wd;

z1 = exp(p1*Ts);
z2 = exp(p2*Ts);

% Additional poles
z3 = 0.7;
z4 = 0.7;

Am = poly([z1 z2 z3 z4]);

disp('Desired polynomial:')
disp(Am)

%% Symbolic RST design

syms r0 r1 r2
syms s0 s1
syms z

Apoly = A(1)*z^2 + A(2)*z + A(3);
Bpoly = B(1)*z + B(2);

R = r2*z^2 + r1*z + r0;
S = z^2 + s1*z + s0;

F = expand(Apoly*S + Bpoly*R);

Am_poly = Am(1)*z^4 + ...
          Am(2)*z^3 + ...
          Am(3)*z^2 + ...
          Am(4)*z   + ...
          Am(5);

CoefF  = coeffs(F,z,'All');
CoefAm = coeffs(Am_poly,z,'All');

sol = solve(CoefF==CoefAm,...
    [r0 r1 r2 s0 s1]);

%% Controller coefficients

Rcoef = double([sol.r2 sol.r1 sol.r0]);
Scoef = double([1 sol.s1 sol.s0]);

disp('R coefficients')
disp(Rcoef)

disp('S coefficients')
disp(Scoef)

%% Prefilter

T = sum(Am)/sum(B);

disp('Prefilter T')
disp(T)

%% Digital controller

C = tf(Rcoef,Scoef,Ts);

%% Open-loop

L = C*Gd;

figure
margin(L)
grid on
title('Open-loop margins')

figure
nyquist(L)
title('Nyquist')

figure
rlocus(L)
title('Root locus')
grid on

%% Sensitivity

Sf = feedback(1,L);

figure
bodemag(Sf)
grid on
title('Sensitivity')

%% Margins

[GM,PM,Wcg,Wcp] = margin(L);

[Ms,wpeak] = getPeakGain(Sf);

Mm = 1/Ms;

fprintf('\n');
fprintf('Gain Margin  = %.2f (%.2f dB)\n',GM,20*log10(GM));
fprintf('Phase Margin = %.2f deg\n',PM);
fprintf('Ms = %.3f\n',Ms);
fprintf('Mm = %.3f\n',Mm);