#include "Blank_3D_Tileset.h"
#include "GameFramework/Actor.h"
Blank_3D_Tileset::Blank_3D_Tileset()
{
}

Blank_3D_Tileset::~Blank_3D_Tileset()
{
}

void Blank_3D_Tileset::InitializeAssetCongifs(const FXmlNode* AssetNode, UWorld* World) {
    TilesetAssetID = FCString::Atoi(*AssetNode->FindChildNode(TEXT("ID"))->GetContent());
    TilesetAssetName = AssetNode->FindChildNode(TEXT("Name"))->GetContent();
    TilesetAssetType = AssetNode->FindChildNode(TEXT("Type"))->GetContent();
    TilesetAssetVisibility = AssetNode->FindChildNode(TEXT("Visibility"))->GetContent();

    const FXmlNode* DetailsNode = AssetNode->FindChildNode(TEXT("Tileset_3D"));
    if (DetailsNode) {
        Blank_3D_Tileset_Url = DetailsNode->FindChildNode(TEXT("Url"))->GetContent();
        const FXmlNode* TMSOverlaysNode = DetailsNode->FindChildNode(TEXT("TileMapServiceOverlays"));
        if (TMSOverlaysNode) {
            for (const FXmlNode* OverlayNode : TMSOverlaysNode->GetChildrenNodes()) {
                Struct_CesiumTileMapServiceRasterOverlay Overlay;
                Overlay.Name = OverlayNode->FindChildNode(TEXT("Name"))->GetContent();
                Overlay.Url = OverlayNode->FindChildNode(TEXT("Url"))->GetContent();
                Overlay.MinZoom = FCString::Atoi(*OverlayNode->FindChildNode(TEXT("MinZoom"))->GetContent());
                Overlay.MaxZoom = FCString::Atoi(*OverlayNode->FindChildNode(TEXT("MaxZoom"))->GetContent());
                Overlay.bSpecifyZoomLevel = OverlayNode->FindChildNode(TEXT("SpecifyZoomLevel"))->GetContent().ToBool();
                Overlay.MaterialLayerKey = OverlayNode->FindChildNode(TEXT("MaterialLayerKey"))->GetContent();
                TMSOverlays.Add(Overlay);
            }
        }


        const FXmlNode* WMSOverlaysNode = DetailsNode->FindChildNode(TEXT("WebMapServiceOverlays"));
        if (WMSOverlaysNode) {
            for (const FXmlNode* OverlayNode : WMSOverlaysNode->GetChildrenNodes()) {
                Struct_CesiumWebMapServiceRasterOverlay Overlay;
                Overlay.Name = OverlayNode->FindChildNode(TEXT("Name"))->GetContent();
                Overlay.BaseUrl = OverlayNode->FindChildNode(TEXT("BaseUrl"))->GetContent();
                Overlay.Layers = OverlayNode->FindChildNode(TEXT("Layers"))->GetContent();
                Overlay.MaterialLayerKey = OverlayNode->FindChildNode(TEXT("MaterialLayerKey"))->GetContent();
                WMSOverlays.Add(Overlay);
            }
        }


        const FXmlNode* WMTSOverlaysNode = DetailsNode->FindChildNode(TEXT("WebMapTileServiceOverlays"));
        if (WMTSOverlaysNode) {
            for (const FXmlNode* OverlayNode : WMTSOverlaysNode->GetChildrenNodes()) {
                Struct_CesiumWebMapTileServiceRasterOverlay Overlay;
                Overlay.Name = OverlayNode->FindChildNode(TEXT("Name"))->GetContent();
                Overlay.BaseUrl = OverlayNode->FindChildNode(TEXT("BaseUrl"))->GetContent();
                Overlay.Layers = OverlayNode->FindChildNode(TEXT("Layers"))->GetContent();
                Overlay.Format = OverlayNode->FindChildNode(TEXT("Format"))->GetContent();
                Overlay.TileMatrixSetID = OverlayNode->FindChildNode(TEXT("TileMatrixSetID"))->GetContent();
                Overlay.TileMatrixSetLabelPrefix = OverlayNode->FindChildNode(TEXT("TileMatrixSetLabelPrefix"))->GetContent();
                Overlay.bSpecifyZoomLevel = OverlayNode->FindChildNode(TEXT("bSpecifyZoomLevel"))->GetContent().ToBool();;
                Overlay.MinZoom = FCString::Atoi(*OverlayNode->FindChildNode(TEXT("MinZoom"))->GetContent());
                Overlay.MaxZoom = FCString::Atoi(*OverlayNode->FindChildNode(TEXT("MaxZoom"))->GetContent());
                Overlay.MaterialLayerKey = OverlayNode->FindChildNode(TEXT("MaterialLayerKey"))->GetContent();
                Overlay.Projection = OverlayNode->FindChildNode(TEXT("Projection"))->GetContent();
                WMTSOverlays.Add(Overlay);
            }
        }


        const FXmlNode* SplatMapNode = DetailsNode->FindChildNode(TEXT("SplatMaps"));
        if (SplatMapNode)
        {
            splatmapdata.Name = SplatMapNode->FindChildNode(TEXT("Name"))->GetContent();

            const FXmlNode* ShpFilesNode = SplatMapNode->FindChildNode(TEXT("ShpFiles"));

            if (ShpFilesNode)          
            {
                for (const FXmlNode* ShpFileNode : ShpFilesNode->GetChildrenNodes())
                {
                    FString Path = ShpFileNode->GetContent();
                    splatmapdata.ShpFilePaths.Add(Path);
                }
            }
        }
    }
}


void Blank_3D_Tileset::InitializeTerrainAssets(UWorld* World) {  
   
    
     Tileset = World->SpawnActor<ACesium3DTileset>();
    if (Tileset) {
        ACesiumGeoreference* GeoreferenceActor = nullptr;
        for (TActorIterator<ACesiumGeoreference> It(World); It; ++It) {
            GeoreferenceActor = *It;
            break;
        }
        Tileset->SetTilesetSource(ETilesetSource::FromUrl);
        Tileset->AttachToActor(GeoreferenceActor, FAttachmentTransformRules::KeepRelativeTransform);
    //    Tileset->SetGenerateSmoothNormals(true);
   
        Tileset->Tags.Add(FName(TilesetAssetName));
#if WITH_EDITOR
        Tileset->SetActorLabel(TilesetAssetName);
#endif



        Tileset->SetUrl(Blank_3D_Tileset_Url);
        for (const Struct_CesiumTileMapServiceRasterOverlay& Overlay : TMSOverlays) {
           // UCesiumTileMapServiceRasterOverlay* RasterOverlay = NewObject<UCesiumTileMapServiceRasterOverlay>(Tileset);

            UCesiumTileMapServiceRasterOverlay* RasterOverlay =
                NewObject<UCesiumTileMapServiceRasterOverlay>(
                    Tileset,
                    UCesiumTileMapServiceRasterOverlay::StaticClass(),
                    *(Overlay.Name + " CesiumTileMapServiceRasterOverlay"),
                    RF_Transactional // so undo/redo works in editor
                );
            if (RasterOverlay) {
                RasterOverlay->Url = Overlay.Url;
                RasterOverlay->MinimumLevel = Overlay.MinZoom;
                RasterOverlay->MaximumLevel = Overlay.MaxZoom;
                RasterOverlay->bSpecifyZoomLevels = Overlay.bSpecifyZoomLevel;
                RasterOverlay->MaterialLayerKey = Overlay.MaterialLayerKey;
                Tileset->AddInstanceComponent(RasterOverlay);
                RasterOverlay->OnComponentCreated();
                Tileset->Modify();
                RasterOverlay->RegisterComponent();
                UTMSOverlays.Add(RasterOverlay);

            }
        }

        for (const Struct_CesiumWebMapServiceRasterOverlay& Overlay : WMSOverlays) {
            UCesiumWebMapServiceRasterOverlay* RasterOverlay =
                NewObject<UCesiumWebMapServiceRasterOverlay>(
                    Tileset,
                    UCesiumWebMapServiceRasterOverlay::StaticClass(),
                    *(Overlay.Name+" CesiumWebMapServiceRasterOverlay"),
                    RF_Transactional // so undo/redo works in editor
                );
            if (RasterOverlay) {
                RasterOverlay->BaseUrl = Overlay.BaseUrl;
                RasterOverlay->Layers = Overlay.Layers;
                RasterOverlay->MaterialLayerKey = Overlay.MaterialLayerKey;
                RasterOverlay->ComponentTags.Add("InternationalBorder");
                Tileset->AddInstanceComponent(RasterOverlay);
                Tileset->Modify();
                RasterOverlay->RegisterComponent();

                UWMSOverlays.Add(RasterOverlay);
            }
        }

        for (const Struct_CesiumWebMapTileServiceRasterOverlay& Overlay : WMTSOverlays) {

            UCesiumWebMapTileServiceRasterOverlay* RasterOverlay =
                NewObject<UCesiumWebMapTileServiceRasterOverlay>(
                    Tileset,
                    UCesiumWebMapTileServiceRasterOverlay::StaticClass(),
                    *(Overlay.Name + " CesiumWebMapTileServiceRasterOverlay"),
                    RF_Transactional // so undo/redo works in editor
                );
            if (RasterOverlay) {
                RasterOverlay->BaseUrl = Overlay.BaseUrl;
                RasterOverlay->Layer = Overlay.Layers;
                RasterOverlay->Format = Overlay.Format;
                RasterOverlay->TileMatrixSetID = Overlay.TileMatrixSetID;
                RasterOverlay->TileMatrixSetLabelPrefix = Overlay.TileMatrixSetLabelPrefix;
                RasterOverlay->bSpecifyZoomLevels = Overlay.bSpecifyZoomLevel;
                RasterOverlay->MinimumLevel = Overlay.MinZoom;
                RasterOverlay->MaximumLevel = Overlay.MaxZoom;
                RasterOverlay->MaterialLayerKey = Overlay.MaterialLayerKey;
                if (Overlay.Projection == "Geographic")
                {
                    RasterOverlay->Projection = ECesiumWebMapTileServiceRasterOverlayProjection::Geographic;
                }
                else if (Overlay.Projection == "WebMercator")
                {
                    RasterOverlay->Projection = ECesiumWebMapTileServiceRasterOverlayProjection::WebMercator;
                }
                
                
                Tileset->AddInstanceComponent(RasterOverlay);
                Tileset->Modify();
                RasterOverlay->RegisterComponent();

                UWMTSOverlays.Add(RasterOverlay);

            }
        }
    }
}


