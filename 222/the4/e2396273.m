N=4145; % size of the Monte Carlo simulation with alpha = 0.05 and error = 0.002
TotalWeight=zeros(N,1); % a vector that keeps the total weight of the passed vehicles for each Monte Carlo run

for k=1:N
% Parameters
lambda_a = 50;   % number of automobiles pass over a bridge 
lambda_aa= 150;  % lambda for weight an automobile 
lambda_t = 10;   % number of trucks pass over a bridge 
lambda_tt= 10;   % lambda for weight a truck
alpha_a = 190;   % alpha  for an automobile 
alpha_t = 110;   % alpha  for a truck

U_a = rand; % Generated Uniform variable for an automobile
U_t = rand; % Generated Uniform variable for a  truck

i = 0; % Initial value i for automobile
j = 0; % Initial value j for truck

F_a = exp(-lambda_a); % Initial value, F(0) for automobile
F_t = exp(-lambda_t); % Initial value, F(0) for truck

while (U_a >= F_a) % The loop ends when U_a < F(i)
F_a = F_a + exp(-lambda_a) * lambda_a^i/gamma(i+1);
i = i + 1;
end

while (U_t >= F_t) % The loop ends when U_t < F(j)
F_t = F_t + exp(-lambda_t) * lambda_t^j/gamma(j+1);
j=j+1;
end

number_of_auto_each_day=i;
number_of_truck_each_day=j;

weight_a = 0; 
weight_t = 0; 
weight=0;

	s = 0; t = 3; m = 0.3;  % the boundary of the rejection sampling rectangle
    
    for f=1:number_of_auto_each_day
        CX = 0; CY = m; % initial coordinates for rejection sampling
        F = 0.3; % initial F at CX = 0

        while (CY > F)
			U = rand; V = rand;
			CX = s+(t-s)*U; CY = m*V;
            mass_auto = sum( -1/lambda_aa * log(rand(alpha_a,1)) );
            mass_auto = mass_auto *1000;
            
        end    
        weight_a=weight_a+mass_auto;

    end


    for f=1:number_of_truck_each_day
        CX = 0; CY = m; % initial coordinates for rejection sampling
        F = 0.3; % initial F at CX = 0
                while (CY > F)
			U = rand; V = rand;
			CX = s+(t-s)*U; CY = m*V;
            mass_truck = sum( -1/lambda_tt * log(rand(alpha_t,1)) );
            mass_truck = mass_truck *1000;
            
                end  
                weight_t=weight_t+mass_truck;
    end         
        weight = weight + weight_a+ weight_t;
         
    TotalWeight(k) = weight;
    
end
p_est = mean(TotalWeight>200000);
expectedWeight = mean(TotalWeight);
stdWeight = std(TotalWeight);
fprintf('Estimated probability = %f\n',p_est);
fprintf('Expected weight = %f\n',expectedWeight);
fprintf('Standard deviation = %f\n',stdWeight);