close all;

syms r0 r1 r2 s2 s1 s0 s;

% System transfer function = B/A
Tr = 7.01; % Time constant
K = 0.17; % Gain
Ts = 0.002; % sampling time
G = tf(K, [Tr 1 0]);
A = Tr*s^2 + s;
B = K;

%% Requirement Tset
PeakTime = 1.5;
Tset = 2;
OS = 2.5;

damping_r = -log(OS/100) / sqrt(pi^2 + log(OS/100)^2);
omega_n = 4 / (damping_r*Tset);


% coefficient of the wanted characteristic equation: d2*s^2 + d1*s + d0
d2 = 1;
d1 = 2*damping_r*omega_n;
d0 = omega_n^2;

%% RST controller calculation
p1 = -3;
p2 = -3.5;
CharEqn = (s^2 + d1*s + d0)*(s-p1)*(s-p2);
% S : degree 2
S = s*(s1*s + s0);
% R : degree 2
R = r2*s^2 + r1*s + r0;

% Characteristic equation
F = A*S + B*R;

%% Coefficient matching
Coef_F = coeffs(expand(F), s, 'All');
Coef_CharEqn = coeffs(expand(CharEqn), s, 'All');
sol = solve(Coef_F == Coef_CharEqn, [r0 r1 r2 s1 s0]);

% Prefilter T
T = double(Coef_CharEqn(5)/K);

r2_d = double(sol.r2)
r1_d = double(sol.r1)
r0_d = double(sol.r0)
s1_d = double(sol.s1)
s0_d = double(sol.s0)

%% Stability and robustness analysis
% Open-loop transfer function
R = tf([r2_d r1_d r0_d],1);
S = tf([s1_d s0_d 0],1);      
C = R/S;
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
