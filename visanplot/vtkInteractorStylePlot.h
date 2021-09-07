//
// Copyright (C) 2002-2021 S[&]T, The Netherlands.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

#ifndef __vtkInteractorStylePlot_h
#define __vtkInteractorStylePlot_h

#include "vtkInteractorStyle.h"
#include "vtkSmartPointer.h"
#include "visanplotModule.h"

class vtkActor2D;
class vtkIndent;
class vtkOutlineSource;
class vtkRenderer;
class vtkPlotActor;

// This interactorstyle only uses VTKIS_NONE, VTKIS_ZOOM, and VTKIS_PAN
// and has an aditional mode VTKIS_OUTLINEZOOM

// Define PlotActor region types
#define VTKIS_Plot_PLOT_AREA 0
#define VTKIS_Plot_X_AXIS 1
#define VTKIS_Plot_Y_AXIS 2
#define VTKIS_Plot_TITLE 3
#define VTKIS_Plot_LEGEND 4

// Define our own VTKIS types
#define VTKIS_OUTLINEZOOM 100

class VISANPLOT_EXPORT vtkInteractorStylePlot : public vtkInteractorStyle
{
    public:
        vtkTypeMacro(vtkInteractorStylePlot, vtkInteractorStyle);
        void PrintSelf(ostream& os, vtkIndent indent) override;

        static vtkInteractorStylePlot *New();

        // Description:
        // Event bindings controlling the effects of pressing mouse buttons
        // or moving the mouse.
        virtual void OnRightButtonDown() override;
        virtual void OnRightButtonUp() override;
        virtual void OnMiddleButtonDown() override;
        virtual void OnMiddleButtonUp() override;
        virtual void OnLeftButtonDown() override;
        virtual void OnLeftButtonUp() override;
        virtual void OnChar() override;
        virtual void OnTimer(void) override;

    protected:
        vtkInteractorStylePlot();

        void Pan() override;
        void OutlineZoom();
        void Zoom() override;

        void StartPan() override;
        void StartOutlineZoom();
        void StartZoom() override;
        void EndOutlineZoom();

        void FindPokedPlotActor(int x, int y);

    protected:
        vtkSmartPointer<vtkPlotActor> CurrentPlotActor;
        int CurrentPlotElement;

        vtkSmartPointer<vtkOutlineSource> OutlineSource;
        vtkSmartPointer<vtkActor2D> OutlineActor;

        double ZoomStartPos[2];                   // only applicable for zooming
        double PrevPos[2];
        double ViewportBounds[4];

    private:
        vtkInteractorStylePlot(const vtkInteractorStylePlot&) = delete;
        void operator=(const vtkInteractorStylePlot&) = delete;
};
#endif