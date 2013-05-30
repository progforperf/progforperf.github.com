subroutine jacobi_line(d,s,top,bottom,front,back,f,n)
    implicit none
    integer :: n
    double precision, dimension(*) :: d,s,top,bottom,front,back,f
    integer :: i,start
    double precision, parameter :: oos=1.d0/6.d0
    do i=2,n-1
       d(i) = oos*(f(i)*s(i)+s(i-1)+s(i+1)+top(i)+bottom(i)+front(i)+back(i))
    enddo
end subroutine


program J3D

use omp_lib
implicit none
double precision :: wct_start,wct_end,cput_start,cput_end,runtime,r
integer :: iter,size,i,j,k,n,t0,t1,t,ofs
double precision, dimension(:,:,:,:), allocatable :: phi
double precision, dimension(:,:,:), allocatable :: f

!print *,'Size?'
read(*,*) size

allocate(phi(1:size,1:size,1:size,0:1))
allocate(f(1:size,1:size,1:size))

t0=0; t1=1
iter=1
runtime=0.d0

do k=1,size
   do j=1,size
      do i=1,size
         phi(i,j,k,0)=i*j
         phi(i,j,k,1)=k*j
         f(i,j,k) = i*k/dble(size*size)
      enddo
   enddo
enddo

do
   call timing(wct_start, cput_start)
   do n=1,iter
!$OMP parallel do 
      do k=2,size-1
         do j=2,size-1
            call jacobi_line(phi(1,j,k,t1),phi(1,j,k,t0),phi(1,j,k-1,t0), &
                 phi(1,j,k+1,t0),phi(1,j-1,k,t0),phi(1,j+1,k,t0),f(1,j,k),size)
         enddo
      enddo
!$OMP end parallel do
      call dummy(phi(1,1,1,t0),phi(1,1,1,t1))
      t=t0; t0=t1; t1=t
   enddo


   call timing(wct_end, cput_end)
   runtime = wct_end-wct_start
   iter = iter * 2
   if(runtime.ge.0.5) exit
enddo

print *,'size: ',size,' iter: ',iter,' MLUP/s: ',dble(iter)/2.d0*(size-2)*(size-2)*(size-2)/runtime/1000000.d0

end
