function z = yuzhi(f)
m = size(f,1);
n = size(f,2);

T = 0.5*(double(min(f(:))) + double(max(f(:))));
done = false;

while ~done
    g = f >= T;
    Tnext = 0.5*(mean(f(g)) + mean(f(~g)));
    done = abs(T - Tnext) < 0.5;
    T = Tnext;
end

z = zeros(size(f));
for i = 1:m
    for j = 1:n
        if f(i,j) > T
            z(i,j) = 255;
        else
            z(i,j) = 0;
        end
    end
end