f0 = 50;
w0 = 2* pi * f0;

zeta = 0.4;
fs = 1000;
Ts = 1/fs;

num_sys = w0^2;
den_sys = [1, 2*w0*zeta, w0^2];
sys_c = tf(num_sys, den_sys)

sys_d = c2d(sys_c, Ts, 'tustin')
