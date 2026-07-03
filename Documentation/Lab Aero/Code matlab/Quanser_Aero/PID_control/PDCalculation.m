close all;

syms s Kp Kd;

% System transfer function = B/A
Tr = 7.01; % Time constant
K = 0.17; % Gain
G = tf(K, [Tr 1 0]);
A = Tr*s^2 + s;
B = K;

%% Requirements
PeakTime = 3.5;
OS = 2.5;

damping_r = -log(OS/100) / sqrt(pi^2 + log(OS/100)^2);
omega_n = pi / (PeakTime*sqrt(1-damping_r^2));
Ts = 4 / (damping_r*omega_n);

% coefficient of the wanted characteristic equation: d2*s^2 + d1*s + d0
d2 = 1;
d1 = 2*damping_r*omega_n;
d0 = omega_n^2;

%% PD controller calculation
CharEqn = (d2*s^2 + d1*s + d0);
PD = Kp + Kd*s;

% Characteristic equation
F = A + B*PD;

% Coefficient matching
Coef_F = coeffs(expand(F), s, 'All');
Coef_F = Coef_F / Coef_F(1);
Coef_CharEqn = coeffs(expand(CharEqn), s, 'All');
sol = solve(Coef_F == Coef_CharEqn, [Kd Kp]);
Kp_d = double(sol.Kp)
Kd_d = double(sol.Kd)

%% Stability and robustness analysis
% Open-loop transfer function
C = tf([Kd_d Kp_d],1);
L = C*G;

% Gain margin and phase margin
figure;
margin(L);
grid on;
title("Bode plot of the system");

figure;
nyquist(L);
title("Nyquist plot of the system");

figure;
rlocus(L);
title("Root locus of the system");
grid on;

% Sensitivy function
S_f = feedback(1,L);
figure;
bodemag(S_f);
title("Magnitude plot of the sensitivity function S");
grid on;

[Ms,wpeak] = getPeakGain(S_f);
Mm = 1/Ms;
[GM, PM, Wcg, Wcp] = margin(L);

fprintf('Gain Margin = %.2f (%.2f dB)\n', GM, 20*log10(GM));
fprintf('Phase Margin = %.2f deg\n', PM);
fprintf('Modulus margin Mm = %.3f\n', Mm);
fprintf('Maximum sensitivity Ms = %.3f\n', Ms);