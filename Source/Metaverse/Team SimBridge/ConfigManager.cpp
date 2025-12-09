// Class Added by Ebaad, This class deals attaching components to a model via config file data
#include "ConfigManager.h"
#include "XmlParser.h"

FModelConfiguration UConfigManager::LoadModelConfigFromXml(const FString& FilePath)
{
    FModelConfiguration Config;
    FXmlFile XmlFile(FilePath);
    if (!XmlFile.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid XML file: %s"), *FilePath);
        return Config;
    }
    const FXmlNode* Root = XmlFile.GetRootNode();
    if (!Root) return Config;
    // ─────────────── <Model> ───────────────
    const FXmlNode* ModelNode = Root->FindChildNode("Model");
    if (ModelNode)
    {
        FModelInfo& Info = Config.ModelInfo;

        auto GetText = [](const FXmlNode* Parent, const FString& Tag) -> FString
            {
                const FXmlNode* Node = Parent->FindChildNode(Tag);
                return Node ? Node->GetContent() : "";
            };
        Info.Title = GetText(ModelNode, "Title");
        Info.Description = GetText(ModelNode, "Description");
        Info.Manufacturer = GetText(ModelNode, "Manufacturer");
        Info.Type = GetText(ModelNode, "Type");
        Info.Variation = GetText(ModelNode, "Variation");
        Info.RoleType = GetText(ModelNode, "RoleType");
        Info.CreatedBy = GetText(ModelNode, "CreatedBy");
        Info.NormalModel = GetText(ModelNode, "NormalModel");
        Info.Sound = GetText(ModelNode, "Sound");
        Info.Texture = GetText(ModelNode, "Texture");
        Info.VisualDamage = FCString::Atoi(*GetText(ModelNode, "VisualDamage"));
        Info.HealthPoints = FCString::Atoi(*GetText(ModelNode, "HealthPoints"));
        Info.DamageModel = GetText(ModelNode, "DamageModel");
        Info.IRTextureName = GetText(ModelNode, "IRTexture");
        Info.DestroyModel = GetText(ModelNode, "DestroyModel");
        Info.BattlespaceModel = GetText(ModelNode, "BattlespaceModel");
        Info.InitialOrientation = GetText(ModelNode, "InitialOrientation");
        Info.DISEntityType = GetText(ModelNode, "DISEntityType");
        Info.ModelHeight = FCString::Atof(*GetText(ModelNode, "ModelHeight"));
        Info.ModelLength = FCString::Atof(*GetText(ModelNode, "ModelLength"));
        Info.ModelWidth = FCString::Atof(*GetText(ModelNode, "ModelWidth"));
        Info.CustomDamagedTexture = GetText(ModelNode, "CustomDamagedTexture").ToBool();
        Info.CustomDestroyedTexture = GetText(ModelNode, "CustomDestroyTexture").ToBool();

    }

    // ─────────────── <Textures> ───────────────
    const FXmlNode* TexturesNode = Root->FindChildNode("Textures");
    if (TexturesNode)
    {
        for (const FXmlNode* Node : TexturesNode->GetChildrenNodes())
        {
            FTextureEntry Tex;
            Tex.Id = FCString::Atoi(*Node->GetAttribute("id"));
            Tex.CountryId = FCString::Atoi(*Node->GetAttribute("country_id"));
            Tex.Name = Node->GetAttribute("name");
            Config.Textures.Add(Tex);
        }
    }

    // ─────────────── <LODs> ───────────────
    const FXmlNode* LODsNode = Root->FindChildNode("LODs");
    if (LODsNode)
    {
        for (const FXmlNode* Node : LODsNode->GetChildrenNodes())
        {
            FLODEntry LOD;
            LOD.Id = FCString::Atoi(*Node->GetAttribute("id"));
            LOD.Name = Node->GetAttribute("Name");
            LOD.Value = FCString::Atof(*Node->GetAttribute("Value"));
            Config.LODs.Add(LOD);
        }
    }

    // ─────────────── <Lights> ───────────────
    const FXmlNode* LightsNode = Root->FindChildNode("Lights");
    if (LightsNode)
    {
        for (const FXmlNode* Node : LightsNode->GetChildrenNodes())
        {
            FModelLightConfig Light;
            Light.Id = FCString::Atoi(*Node->GetAttribute("id"));
            Light.RefNode = Node->GetAttribute("RefNode");
            Light.VFX = Node->GetAttribute("vfx");
            Config.Lights.Add(Light);
        }
    }

    // ─────────────── <Effects> ───────────────
    const FXmlNode* EffectsNode = Root->FindChildNode("Effects");
    if (EffectsNode)
    {
        for (const FXmlNode* Node : EffectsNode->GetChildrenNodes())
        {
            FModelEffectConfig Effect;
            Effect.Type = Node->GetAttribute("type");
            Effect.Sound = Node->GetAttribute("sound");
            Effect.Event = Node->GetAttribute("event");
            Effect.RefNode = Node->GetAttribute("RefNode");
            Effect.VFX = Node->GetAttribute("vfx");
            Config.Effects.Add(Effect);
        }
    }

    // ─────────────── <GroundSupportPoints> ───────────────
    const FXmlNode* GSPNode = Root->FindChildNode("GroundSupportPoints");
    if (GSPNode)
    {
        for (const FXmlNode* Node : GSPNode->GetChildrenNodes())
        {
            FSupportPoint Pt;
            Pt.Id = FCString::Atoi(*Node->GetAttribute("id"));
            Pt.RefNode = Node->GetAttribute("RefNode");
            Config.SupportPoints.Add(Pt);
        }
    }

    // ─────────────── <ArticulatedParts> ───────────────
    const FXmlNode* PartsNode = Root->FindChildNode("ArticulatedParts");
    if (PartsNode)
    {
        for (const FXmlNode* Node : PartsNode->GetChildrenNodes())
        {
            FArticulatedPart Part;
            Part.Id = FCString::Atoi(*Node->GetAttribute("id"));
            Part.Category = Node->GetAttribute("category");
            Part.State = Node->GetAttribute("state");
            Part.Type = Node->GetAttribute("type");
            Part.RefNodes = Node->GetAttribute("RefNodes");
            Part.AnimationSeq = Node->GetAttribute("animationSeq");

            for (const FXmlNode* EffectNode : Node->GetChildrenNodes())
            {
                FArticulatedEffect FX;
                FX.Event = EffectNode->GetAttribute("event");
                FX.VFX = EffectNode->GetAttribute("vfx");
                FX.Sound = EffectNode->GetAttribute("sound");
                FX.RefNode = EffectNode->GetAttribute("RefNode");
                Part.Effects.Add(FX);
            }

            Config.ArticulatedParts.Add(Part);
        }
    }

    // ─────────────── <Attachments> ───────────────
    const FXmlNode* AttachmentsNode = Root->FindChildNode("Attachments");
    if (AttachmentsNode)
    {
        for (const FXmlNode* Node : AttachmentsNode->GetChildrenNodes())
        {
            FAttachment Attach;
            Attach.Id = FCString::Atoi(*Node->GetAttribute("id"));
            Attach.RefNode = Node->GetAttribute("RefNode");
            Attach.PartNo = FCString::Atoi(*Node->GetAttribute("PartNo"));
            Attach.StationNo = FCString::Atoi(*Node->GetAttribute("StationNo"));
            Attach.Orientation = Node->GetAttribute("Orientation");
            Config.Attachments.Add(Attach);
        }
    }

    // ─────────────── <Camera> ───────────────
    const TArray<FXmlNode*> CameraNodes = Root->GetChildrenNodes();
    for (const FXmlNode* Node : CameraNodes)
    {
        if (Node->GetTag() == "Camera")
        {
            FCameraConfig Cam;
            Cam.Id = FCString::Atoi(*Node->GetAttribute("id"));

            auto GetSafeContent = [](const FXmlNode* Parent, const FString& Tag) -> FString
                {
                    const FXmlNode* Child = Parent->FindChildNode(Tag);
                    return Child ? Child->GetContent() : "";
                };

            Cam.Title = GetSafeContent(Node, "Title");
            Cam.Description = GetSafeContent(Node, "Description");
            Cam.Origin = GetSafeContent(Node, "Origin");
            Cam.AllowZoom = GetSafeContent(Node, "AllowZoom").ToBool();
            Cam.InitialZoom = FCString::Atof(*GetSafeContent(Node, "InitialZoom"));
            Cam.ZoomFactor = FCString::Atof(*GetSafeContent(Node, "ZoomFactor"));
            Cam.InitialXyz = GetSafeContent(Node, "InitialXyz");
            Cam.InitialOrientation = GetSafeContent(Node, "InitialOrientation");
            Cam.ShowLensFlare = GetSafeContent(Node, "ShowLensFlare").ToBool();
            Cam.Category = GetSafeContent(Node, "Category");
            Cam.CameraType = GetSafeContent(Node, "CameraType");

            Config.Cameras.Add(Cam);
        }
    }


    UE_LOG(LogTemp, Display, TEXT(" Loaded config with %d lights, %d effects, %d attachments, %d articulated parts."),
        Config.Lights.Num(), Config.Effects.Num(), Config.Attachments.Num(), Config.ArticulatedParts.Num());

    return Config;
}
