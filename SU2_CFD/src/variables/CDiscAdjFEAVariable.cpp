/*!
 * \file CDiscAdjFEAVariable.cpp
 * \brief Definition of the variables for FEM adjoint elastic structural problems.
 * \author R. Sanchez
 * \version 7.1.1 "Blackbird"
 *
 * SU2 Project Website: https://su2code.github.io
 *
 * The SU2 Project is maintained by the SU2 Foundation
 * (http://su2foundation.org)
 *
 * Copyright 2012-2021, SU2 Contributors (cf. AUTHORS.md)
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */


#include "../../include/variables/CDiscAdjFEAVariable.hpp"


CDiscAdjFEAVariable::CDiscAdjFEAVariable(const su2double *disp, const su2double *vel, const su2double *accel, unsigned long npoint,
  unsigned long ndim, unsigned long nvar, bool unsteady, CConfig *config) : CVariable(npoint, ndim, nvar, config) {

  Solution_Direct.resize(nPoint,nDim);
  if (config->GetTime_Domain()) nVar = 3*nDim;
  Sensitivity.resize(nPoint,nDim) = su2double(0.0);
  Sensitivity_Old.resize(nPoint,nDim) = su2double(0.0);

  for (unsigned long iPoint = 0; iPoint < nPoint; ++iPoint) {
    if (config->GetTime_Domain()) {
      for (unsigned long iVar = 0; iVar < nDim; iVar++)
        Solution(iPoint,iVar) = disp[iVar];
      for (unsigned long iVar = nDim; iVar < 2*nDim; iVar++)
        Solution(iPoint,iVar) = vel[iVar];
      for (unsigned long iVar = 2*nDim; iVar < 3*nDim; iVar++)
        Solution(iPoint,iVar) = accel[iVar];
    }
    else {
      for (unsigned long iVar = 0; iVar < nVar; iVar++)
        Solution(iPoint,iVar) = disp[iVar];
    }
  }

  if (config->GetMultizone_Problem() && config->GetDiscrete_Adjoint()) {
    External.resize(nPoint,nVar) = su2double(0.0);
  }

  /*--- Nothing else to allocate ---*/
  if (!unsteady) return;

cout << "CVC: Debug: nVar = " << nVar << endl;
  Dynamic_Derivative.resize(nPoint,nVar) = su2double(0.0);
  Dynamic_Derivative_n.resize(nPoint,nVar) = su2double(0.0);

  Solution_Direct_Vel.resize(nPoint,nDim) = su2double(0.0);
  Solution_Direct_Accel.resize(nPoint,nDim) = su2double(0.0);

}
