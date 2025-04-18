program adi
  use omp_lib
  implicit none
!
  integer, parameter :: dp = kind(1.0d0)
  integer :: i, j, iter
  integer, parameter :: npoints = 2000, maxiter = 400
  real (kind=dp) :: start, finish
  real (kind=dp) :: tmp, diff, maxdiff
  real (kind=dp) :: a(npoints,npoints), b(npoints,npoints), x(npoints,npoints) 


  start = omp_get_wtime()

  do j = 1,npoints 
     do i = 1,npoints 
         a(i,j) = 1.0d0
         b(i,j) = 3.14159265359d0
         x(i,j) = 1.0d0
     end do
  end do

  maxdiff = 0.0d0

  do iter = 1,maxiter

     do j = 2,npoints 
        do i = 1,npoints 
           tmp = a(i,j)/b(i,j-1) 
           x(i,j) = x(i,j) - x(i,j-1) * tmp
           b(i,j) = b(i,j) - a(i,j) * tmp        
        end do
     end do

     diff = 0.0d0

     do j = 1,npoints 
        do i = 2,npoints 
           tmp = a(i,j)/b(i-1,j) 
           x(i,j) = x(i,j) - x(i-1,j) * tmp
           b(i,j) = b(i,j) - a(i,j) * tmp        
           diff = diff + abs(a(i,j) * tmp) / (npoints * npoints) 
        end do
     end do

     maxdiff = max(diff,maxdiff) 

  end do 

  finish = omp_get_wtime()
!
! Output results
!
  write (*,'(A, F12.8)') "Max Diff = ",maxdiff
  print *, "Time  = ", finish-start, " seconds"
!
  stop
end program adi
