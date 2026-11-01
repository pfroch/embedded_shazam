% Signal Parameters
Fs = 1000;            
T = 1/Fs;             
L = 1000;     %samples        
t = (0:L-1)*T;       


signal = 0.7 * sin(2*pi*50*t) + sin(2*pi*120*t);
noisySignal = signal + 2*randn(size(t)); %noise


Y = fft(noisySignal);


P2 = abs(Y/L);          
P1 = P2(1:L/2+1);       
P1(2:end-1) = 2*P1(2:end-1);


f = Fs*(0:(L/2))/L;


figure;
plot(f, P1, 'LineWidth', 1.5);
title('Single-Sided Amplitude Spectrum of Noisy Signal');
xlabel('Frequency (Hz)');
ylabel('|P1(f)|');
grid on;