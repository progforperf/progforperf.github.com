void fast(smat_t *a)
{
	int i, j;
	double x1,x2;


	//Get rid of the pointer indirections
	int n = a->n; 
	double * mat = a->mat;

	//Change the loop order to make sure that the expensive sin and cos are only compute once
	for(i = 0; i < n; i=i+4)
	{
		double m[2][2];		
		m[0][0] = cos(i);
		m[0][1] = sin(i);
		m[1][0] = -sin(i);
		m[1][1] = cos(i);


		// j is the column of a we're computing right now
		for(j = 0; j < n; j++)
		{            
			// First, compute f(A) for the element of a in question
			x1 = mat[i*n+j];
			x2 = mat[ (i+1)*n+j];

			x1 = m[0][0] * x1 + m[0][1]* x2 + x1;
			x2 = m[1][0] * x1 + m[1][1]* x2 + x2;

			// Add this to the value of a we're computing and store it                
			mat[i*n+j] = x1;
			mat[ (i+1)*n+j] = x2;
		}
	}
	//Split the if into two loops - since we will still fit in cache this will pay off 
	for(i = 2; i < n; i=i+4)
	{
		double m[2][2];		
		m[0][0] = cos(-i);
		m[0][1] = sin(-i);
		m[1][0] = -sin(-i);
		m[1][1] = cos(-i);


		// j is the column of a we're computing right now
		for(j = 0; j < n; j++)
		{            
			// First, compute f(A) for the element of a in question
			x1 = mat[i*n+j];
			x2 = mat[ (i+1)*n+j];

			x1 = m[0][0] * x1 + m[0][1]* x2 + x1;
			x2 = m[1][0] * x1 + m[1][1]* x2 + x2;

			// Add this to the value of a we're computing and store it                
			mat[i*n+j] = x1;
			mat[ (i+1)*n+j] = x2;

		}
	}

}