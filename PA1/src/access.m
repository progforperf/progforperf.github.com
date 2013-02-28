for n = 100:10:1000
  tic;
    A = [];
    for i = 1:n
      A(i,i) = 1;
    end
  times(n) = toc;
end
